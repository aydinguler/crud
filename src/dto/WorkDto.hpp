#ifndef WorkDto_hpp
#define WorkDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

ENUM(TaskState, v_int32,
    VALUE(False, 0, "False"),
    VALUE(True, 1, "True")
)

class WorkDto : public oatpp::DTO {

    DTO_INIT(WorkDto, DTO)

    DTO_FIELD(Int32, taskID);
    DTO_FIELD(String, taskName, "taskName");
    DTO_FIELD(Enum<TaskState>::AsString, taskState, "taskState");
    DTO_FIELD(String, taskDueDate, "taskDueDate");
    DTO_FIELD(String, taskCreationDate, "taskCreationDate");

};

#include OATPP_CODEGEN_END(DTO)

#endif /* WorkDto_hpp */
