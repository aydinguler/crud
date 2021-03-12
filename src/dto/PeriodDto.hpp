#ifndef PeriodDto_hpp
#define PeriodDto_hpp

#include "WorkDto.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

template<class T>
class PeriodDto : public oatpp::DTO {

  DTO_INIT(PeriodDto, DTO)

  DTO_FIELD(UInt32, count);
  DTO_FIELD(Vector<T>, items);

};

class WorksPeriodDto : public PeriodDto<oatpp::Object<WorkDto>> {

  DTO_INIT(WorksPeriodDto, PeriodDto<oatpp::Object<WorkDto>>)

  DTO_FIELD(String, untilThatDate, "untilThatDate");

};

#include OATPP_CODEGEN_END(DTO)

#endif //PeriodDto_hpp
