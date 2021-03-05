# CRUD

A complete "CRUD" service (TaskService) built with Oat++.

In this project:

- CRUD endpoints are created.
- [oatpp ORM](https://oatpp.io/docs/components/orm/#high-level-overview) - SQLite example is used.
- API is documented with Swagger-UI and OpenApi 3.0.0.

## Overview

This project is using the following oatpp modules:

- [oatpp](https://github.com/oatpp/oatpp) 
- [oatpp-swagger](https://github.com/oatpp/oatpp-swagger)
- [oatpp-sqlite](https://github.com/oatpp/oatpp-sqlite)

### Project layout

```
|- CMakeLists.txt                        // projects CMakeLists.txt
|- sql/                                  // SQL migration scripts for SQLite database
|- src/
|   |
|   |- controller/                       // Folder containing REST Controllers (WorkController)
|   |- db/                               // Folder containing the database client
|   |- dto/                              // DTOs are declared here
|   |- service/                          // Service business logic classes (WorkService)
|   |- AppComponent.hpp                  // Service config
|   |- DatabaseComponent.hpp             // Database config
|   |- SwaggerComponent.hpp              // Swagger-UI config
|   |- App.cpp                           // main() is here
|
|- test/                                 // test folder
|- utility/install-oatpp-modules.sh      // utility script to install required oatpp-modules.
```

---

### Build and Run

#### Using CMake

##### Pre Requirements

- `oatpp` 
- `oatpp-swagger`
- `oatpp-sqlite` with `-DOATPP_SQLITE_AMALGAMATION=ON` cmake flag.

**Note:** You may run `utility/install-oatpp-modules.sh` script to install required oatpp modules.

##### Build Project

```
$ mkdir build && cd build
$ cmake ..
$ make 
$ ./crud-exe        # - run application.
```

#### In Docker

```
$ docker build -t example-crud .
$ docker run -p 8000:8000 -t example-crud
```

---

### Endpoints 

#### HTML

|HTTP Method|URL|Description|
|---|---|---|
|`GET`|http://localhost:8000/ | Root page |
|`GET`|http://localhost:8000/swagger/ui | Swagger UI page |

#### Work Service

|HTTP Method|URL|Description|
|---|---|---|
|`POST`|http://localhost:8000/Work/Add | Create new Work |
|`PUT`|http://localhost:8000/Work/ChangeState/{workID} | Change Work State by workID |
|`DELETE`|http://localhost:8000/Work/Delete/{workID} | Delete Work by workID |
|`GET`|http://localhost:8000/Work/GetById/{workID} | Get Work by workID |
|`GET`|http://localhost:8000/Work/offset/{offset}/limit/{limit} | Get the Specified Amount of Works with Paging |
