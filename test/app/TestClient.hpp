#ifndef DatabaseTestClient_hpp
#define DatabaseTestClient_hpp

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include "dto/WorkDto.hpp"

/* Begin Api Client code generation */
#include OATPP_CODEGEN_BEGIN(ApiClient)

/**
 * Test API client.
 * Use this client to call application APIs.
 */
class TestClient : public oatpp::web::client::ApiClient {

  API_CLIENT_INIT(TestClient)

  /*****************************************************************
   * WorkController
   *****************************************************************/

  API_CALL("POST", "/Work/Add", addWork, BODY_DTO(Object<WorkDto>, workDto))
  API_CALL("GET", "/Work/GetById/{workId}", getWork, PATH(Int32, workId))
  API_CALL("DELETE", "/Work/Delete/{workId}", deleteWork, PATH(Int32, workId))

  /*****************************************************************/

  // TODO - add more client API calls here

};

/* End Api Client code generation */
#include OATPP_CODEGEN_END(ApiClient)

#endif // DatabaseTestClient_hpp