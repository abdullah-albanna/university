## Creating the Table

```sql
CREATE TABLE engineers (
    id NUMBER PRIMARY KEY,
    name VARCHAR2(100) NOT NULL,
    departments VARCHAR2(100),
    salary NUMBER
);
```

## Renames

```sql
ALTER TABLE engineers RENAME TO ENG;
```

```sql
ALTER TABLE ENG RENAME COLUMN id TO eng_id;
```

```sql
desc ENG;

-- Name        | Null? | Type
-- ------------|-------|---------
-- ENG_ID      | NO    | NUMBER
-- NAME        | NO    | VARCHAR2(100)
-- DEPARTMENTS | YES   | VARCHAR2(100)
-- SALARY      | YES   | NUMBER
```

## Adds

```sql
ALTER TABLE ENG ADD DOB DATE;
```

```sql
ALTER TABLE ENG  ADD (email VARCHAR2(100), experience_years NUMBER);
```

## Drops

```sql
ALTER TABLE ENG DROP COLUMN salary;
```

```sql
desc ENG;


-- Name             | Null? | Type
-- -----------------|-------|---------
-- ENG_ID           | NO    | NUMBER
-- NAME             | NO    | VARCHAR2(100)
-- DEPARTMENTS      | YES   | VARCHAR2(100)
-- DOB              | YES   | DATE
-- EMAIL            | YES   | VARCHAR2(100)
-- EXPERIENCE_YEARS | YES   | NUMBER
```
