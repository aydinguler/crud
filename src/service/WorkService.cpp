
#include "WorkService.hpp"

oatpp::Object<WorkDto> WorkService::createWork(const oatpp::Object<CreateWorkDto>& dto) {

    auto dbResult = m_database->createWork(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto workID = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());

    return getWorkById((v_int32)workID);

}

oatpp::Object<StatusDto> WorkService::ChangeState(const oatpp::Object<ChangeStateDto>& dto) {

    auto dbResult = m_database->ChangeState(dto);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto workID = oatpp::sqlite::Utils::getLastInsertRowId(dbResult->getConnection());
    auto status = StatusDto::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Work status was successfully changed";
    return status;


}

oatpp::Object<WorkDto> WorkService::getWorkById(const oatpp::Int32& taskID, const std::shared_ptr<oatpp::orm::Connection>& connection) {

    auto dbResult = m_database->getWorkById(taskID, connection);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    OATPP_ASSERT_HTTP(dbResult->hasMoreToFetch(), Status::CODE_404, "Work not found");

    auto result = dbResult->fetch<oatpp::Vector<oatpp::Object<WorkDto>>>();
    OATPP_ASSERT_HTTP(result->size() == 1, Status::CODE_500, "Unknown error");

    return result[0];

}

oatpp::Object<PageDto<oatpp::Object<WorkDto>>> WorkService::getAllWorks(const oatpp::UInt32& offset, const oatpp::UInt32& limit) {

    oatpp::UInt32 countToFetch = limit;

    auto dbResult = m_database->getAllWorks(offset, countToFetch);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<WorkDto>>>();

    auto page = PageDto<oatpp::Object<WorkDto>>::createShared();
    page->offset = offset;
    page->limit = countToFetch;
    page->count = items->size();
    page->items = items;

    return page;

}

oatpp::Object<StatusDto> WorkService::deleteWorkById(const oatpp::Int32& workID) {
    auto dbResult = m_database->deleteWorkById(workID);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());
    auto status = StatusDto::createShared();
    status->status = "OK";
    status->code = 200;
    status->message = "Work was successfully deleted";
    return status;
}

oatpp::Object<PeriodDto<oatpp::Object<WorkDto>>> WorkService::getAllWorksDueDate(const oatpp::String& untilThatDate) {


    auto dbResult = m_database->getAllWorksDueDate(untilThatDate);
    OATPP_ASSERT_HTTP(dbResult->isSuccess(), Status::CODE_500, dbResult->getErrorMessage());

    auto items = dbResult->fetch<oatpp::Vector<oatpp::Object<WorkDto>>>();

    auto page = PeriodDto<oatpp::Object<WorkDto>>::createShared();
    page->count = items->size();
    page->items = items;

    return page;

}