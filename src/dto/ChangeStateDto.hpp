#ifndef ChangeStateDto_hpp
#define ChangeStateDto_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ChangeStateDto : public oatpp::DTO {

    DTO_INIT(ChangeStateDto, DTO)

    DTO_FIELD(Int32, taskID, "taskID");

};

#include OATPP_CODEGEN_END(DTO)

#endif /* ChangeStateDto_hpp */
