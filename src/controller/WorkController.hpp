
#ifndef WorkController_hpp
#define WorkController_hpp

#include "service/WorkService.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

/**
 * Work REST controller.
 */
class WorkController : public oatpp::web::server::api::ApiController {
public:
    WorkController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
        : oatpp::web::server::api::ApiController(objectMapper)
    {}
private:
    WorkService m_workService; // Create work service.
public:

    static std::shared_ptr<WorkController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
    ) {
        return std::make_shared<WorkController>(objectMapper);
    }

    ENDPOINT_INFO(createWork) {
        info->summary = "Create new work";

        info->addConsumes<Object<WorkDto>>("application/json");

        info->addResponse<Object<WorkDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("POST", "Work/Add", createWork,
        BODY_DTO(Object<WorkDto>, workDto))
    {
        return createDtoResponse(Status::CODE_200, m_workService.createWork(workDto));
    }


    ENDPOINT_INFO(putWork) {
        info->summary = "Update work by workID";

        info->addConsumes<Object<WorkDto>>("application/json");

        info->addResponse<Object<WorkDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["workID"].description = "Work Identifier";
    }
    ENDPOINT("PUT", "Work/ChangeState/{workID}", putWork,
        PATH(Int32, workID),
        BODY_DTO(Object<WorkDto>, workDto))
    {
        workDto->taskID = workID;
        return createDtoResponse(Status::CODE_200, m_workService.ChangeState(workDto));
    }


    ENDPOINT_INFO(deleteWork) {
        info->summary = "Delete work by workID";

        info->addResponse<Object<StatusDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["workID"].description = "Work Identifier";
    }
    ENDPOINT("DELETE", "Work/Delete/{workID}", deleteWork,
        PATH(Int32, workID))
    {
        return createDtoResponse(Status::CODE_200, m_workService.deleteWorkById(workID));
    }


    ENDPOINT_INFO(getWorkById) {
        info->summary = "Get one work by workID";

        info->addResponse<Object<WorkDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_404, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");

        info->pathParams["workID"].description = "Work Identifier";
    }
    ENDPOINT("GET", "Work/GetById/{workID}", getWorkById,
        PATH(Int32, workID))
    {
        return createDtoResponse(Status::CODE_200, m_workService.getWorkById(workID));
    }


    ENDPOINT_INFO(getWorks) {
        info->summary = "Get the specified amount of works";

        info->addResponse<oatpp::Object<WorksPageDto>>(Status::CODE_200, "application/json");
        info->addResponse<Object<StatusDto>>(Status::CODE_500, "application/json");
    }
    ENDPOINT("GET", "Work/offset/{offset}/limit/{limit}", getWorks,
        PATH(UInt32, offset),
        PATH(UInt32, limit))
    {
        return createDtoResponse(Status::CODE_200, m_workService.getAllWorks(offset, limit));
    }




};

#include OATPP_CODEGEN_BEGIN(ApiController) //<- End Codegen

#endif /* WorkController_hpp */
