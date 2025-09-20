# PK Requirements

- Unique
- Not Null
- Only one

# A constraint that doesn't get applied at table level

- Not Null

# Doctors

## Creating the Table

```sql
CREATE TABLE Doctors (
ID NUMBER,
doc_name VARCHAR2(100) NOT NULL,
DOE DATE NOT NULL,
Status VARCHAR2(20) CHECK (Status IN ('Single', 'Married')),
Salary NUMBER,
Account_number NUMBER,

CONSTRAINT pk_doctors PRIMARY KEY (ID),
CONSTRAINT uq_account UNIQUE (Account_number),
CONSTRAINT chk_salary CHECK (Salary > 50000)
);
```

```sql
ALTER TABLE Doctors DROP CONSTRAINT chk_salary;
```

---

# Depts

## Creating the Table

```sql
CREATE TABLE Dept (
    ID NUMBER,
    name VARCHAR2(50) UNIQUE CHECK (Name IN ('IT','CS','IS')),
    head VARCHAR2(100),
    NOS NUMBER CHECK ( NOS BETWEEN 30 AND 100 )
);
```

```sql
ALTER TABLE Dept ADD CONSTRAINT pk_dept PRIMARY KEY (ID);
```

```sql
ALTER TABLE Dept ADD (
        CONSTRAINT nn_head CHECK (Head IS NOT NULL),
        CONSTRAINT chk_nos CHECK (NOS BETWEEN 30 AND 100)
    );
```

```sql
ALTER TABLE Dept DROP CONSTRAINT nn_head;
```
