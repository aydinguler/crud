
#ifndef CRUD_WORKDB_HPP
#define CRUD_WORKDB_HPP

#include "dto/WorkDto.hpp"
#include "oatpp-sqlite/orm.hpp"
#include "dto/CreateWorkDto.hpp"
#include "dto/ChangeStateDto.hpp"

#include OATPP_CODEGEN_BEGIN(DbClient) //<- Begin Codegen

/**
 * WorkDb client definitions.
 */
class WorkDb : public oatpp::orm::DbClient {
public:

    WorkDb(const std::shared_ptr<oatpp::orm::Executor>& executor)
        : oatpp::orm::DbClient(executor)
    {

        oatpp::orm::SchemaMigration migration(executor);
        migration.addFile(1 /* start from version 1 */, DATABASE_MIGRATIONS "/001_init.sql");
        // TODO - Add more migrations here.
        migration.migrate(); // <-- run migrations. This guy will throw on error.

        auto version = executor->getSchemaVersion();
        OATPP_LOGD("WorkDb", "Migration - OK. Version=%d.", version);

    }

        QUERY(createWork,
            "INSERT INTO AppWork"
            "(taskName, taskState, taskCreationDate, taskDueDate) VALUES "
            "(:work.taskName, 'False', date('now','localtime'), :work.taskDueDate);",
            PARAM(oatpp::Object<CreateWorkDto>, work))

        QUERY(ChangeState,
            "UPDATE AppWork "
            "SET "
            " taskState='True' "
            "WHERE "
            " taskID=:work.taskID;",
            PARAM(oatpp::Object<ChangeStateDto>, work))

        QUERY(getWorkById,
            "SELECT * FROM Appwork WHERE taskID=:taskID;",
            PARAM(oatpp::Int32, taskID))

        QUERY(getAllWorks,
            "SELECT * FROM AppWork LIMIT :limit OFFSET :offset;",
            PARAM(oatpp::UInt32, offset),
            PARAM(oatpp::UInt32, limit))

        QUERY(deleteWorkById,
            "DELETE FROM AppWork WHERE taskID=:taskID;",
            PARAM(oatpp::Int32, taskID))

        QUERY(getAllWorksDueDate,
            "SELECT * FROM AppWork WHERE taskDueDate BETWEEN date('now','localtime') AND :untilThatDate;",
            PARAM(oatpp::String, untilThatDate))

};

#include OATPP_CODEGEN_END(DbClient) //<- End Codegen

#endif //CRUD_WORKDB_HPP
