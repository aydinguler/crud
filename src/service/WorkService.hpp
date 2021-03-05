
#ifndef CRUD_WORKSERVICE_HPP
#define CRUD_WORKSERVICE_HPP

#include "db/WorkDb.hpp"
#include "dto/PageDto.hpp"
#include "dto/StatusDto.hpp"

#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/core/macro/component.hpp"

class WorkService {
private:
	typedef oatpp::web::protocol::http::Status Status;
private:
	OATPP_COMPONENT(std::shared_ptr<WorkDb>, m_database); // Inject database component
public:

	oatpp::Object<WorkDto> createWork(const oatpp::Object<WorkDto>& dto);
	oatpp::Object<WorkDto> ChangeState(const oatpp::Object<WorkDto>& dto);
	oatpp::Object<WorkDto> getWorkById(const oatpp::Int32& taskID, const std::shared_ptr<oatpp::orm::Connection>& connection = nullptr);
	oatpp::Object<PageDto<oatpp::Object<WorkDto>>> getAllWorks(const oatpp::UInt32& offset, const oatpp::UInt32& limit);
	oatpp::Object<StatusDto> deleteWorkById(const oatpp::Int32& taskID);

};

#endif //CRUD_USERSERVICE_HPP