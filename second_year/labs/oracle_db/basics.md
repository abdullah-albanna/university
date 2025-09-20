## Basic syntax for CREATE TABLE

```sql
CREATE TABLE table_name (
    column1 datatype,
);
```

## Creating `doctors` Table

```sql
CREATE TABLE doctors (
    doctor_id NUMBER PRIMARY KEY,
    name VARCHAR2(100) NOT NULL,
    specialty VARCHAR2(50),
    salary NUMBER,
    hire_date DATE
);
```

## How to Drop a Table (and also drop it)

```sql
DROP TABLE table_name;
```

```sql
DROP TABLE doctors;
```
