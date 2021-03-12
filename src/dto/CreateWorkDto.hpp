#ifndef CreateWorkDto_hpp
#define CreateWorkDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class CreateWorkDto : public oatpp::DTO {

    DTO_INIT(CreateWorkDto, DTO)

        DTO_FIELD(String, taskName, "taskName");
    DTO_FIELD(String, taskDueDate, "taskDueDate");

};

#include OATPP_CODEGEN_END(DTO)

#endif /* CreateWorkDto_hpp */
