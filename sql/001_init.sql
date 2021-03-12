
CREATE TABLE AppWork (
    taskID              INTEGER PRIMARY KEY,
    taskName            VARCHAR UNIQUE,
    taskState           VARCHAR,
    taskCreationDate    TEXT,
    taskDueDate         TEXT
);
