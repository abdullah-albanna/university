CREATE TABLE doctors (
  id int,
  name VARCHAR2(100),
  department VARCHAR2(50),
  salary int
);

ALTER TABLE doctors RENAME TO Doct;

ALTER TABLE Doct RENAME COLUMN name TO full_name;

DESC Doct;

ALTER TABLE Doct ADD (dob DATE);

DESC Doct;

ALTER TABLE Doct ADD (phone NUMBER(9), nationality VARCHAR2(100));

ALTER TABLE Doct DROP COLUMN department;

DESC Doct;
