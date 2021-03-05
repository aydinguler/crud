#include "WorkControllerTest.hpp"

#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp-test/web/ClientServerTestRunner.hpp"

#include "controller/WorkController.hpp"

#include "app/TestClient.hpp"
#include "app/TestComponent.hpp"

#include <cstdio>

void WorkControllerTest::onRun() {

    /* Remove test database file before running the test */
    OATPP_LOGI(TAG, "DB-File='%s'", TESTDATABASE_FILE);
    std::remove(TESTDATABASE_FILE);

    /* Register test components */
    TestComponent component;

    /* Create client-server test runner */
    oatpp::test::web::ClientServerTestRunner runner;

    /* Add WorkController endpoints to the router of the test server */
    runner.addController(std::make_shared<WorkController>());

    /* Run test */
    runner.run([this, &runner] {

        /* Get client connection provider for Api Client */
        OATPP_COMPONENT(std::shared_ptr<oatpp::network::ClientConnectionProvider>, clientConnectionProvider);

        /* Get object mapper component */
        OATPP_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, objectMapper);

        /* Create http request executor for Api Client */
        auto requestExecutor = oatpp::web::client::HttpRequestExecutor::createShared(clientConnectionProvider);

        /* Create Test API client */
        auto client = TestClient::createShared(requestExecutor, objectMapper);

        auto dto = WorkDto::createShared();

        dto->taskName = "jondoe";

        /* Call server API */
        auto addedWorkResponse = client->addWork(dto);

        /* Assert that server responds with 200 */
        OATPP_ASSERT(addedWorkResponse->getStatusCode() == 200);

        /* Read response body as MessageDto */
        auto addedWorkDto = addedWorkResponse->readBodyToDto<oatpp::Object<WorkDto>>(objectMapper.get());

        int addedWorkId = addedWorkDto->taskID;

        /* Assert that work has been added */
        auto newWorkResponse = client->getWork(addedWorkId);

        OATPP_ASSERT(newWorkResponse->getStatusCode() == 200);

        auto newWorkDto = newWorkResponse->readBodyToDto<oatpp::Object<WorkDto>>(objectMapper.get());

        OATPP_ASSERT(newWorkDto->taskID == addedWorkId);

        /* Delete newly added works */
        auto deletedWorkResponse = client->deleteWork(addedWorkId);

        OATPP_ASSERT(deletedWorkResponse->getStatusCode() == 200);

        }, std::chrono::minutes(10) /* test timeout */);

    /* wait all server threads finished */
    std::this_thread::sleep_for(std::chrono::seconds(1));

    /* stop db connection pool */
    OATPP_COMPONENT(std::shared_ptr<oatpp::provider::Provider<oatpp::sqlite::Connection>>, dbConnectionProvider);
    dbConnectionProvider->stop();

}