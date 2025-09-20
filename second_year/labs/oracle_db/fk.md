# 1:1

```sql
CREATE TABLE Certs (
    ID NUMBER PRIMARY KEY,
    Release_Date DATE,
    Release_Location VARCHAR2(100)
);
```

```sql
CREATE TABLE Students (
    ID NUMBER PRIMARY KEY,
    Name VARCHAR2(100),
    Age NUMBER,
    BD DATE,
    Phone_Number NUMBER,
    Gender VARCHAR2(10),
    Cert NUMBER UNIQUE,
    CONSTRAINT fk_cert FOREIGN KEY (Cert) REFERENCES Certs(ID)
);
```

```sql
ALTER TABLE Students ADD Cert NUMBER;
```

```sql
ALTER TABLE Students ADD CONSTRAINT fk_cert FOREIGN KEY (Cert) REFERENCES Certs(ID);
```

---

# 1:M

```sql
CREATE TABLE Dep (
    ID NUMBER PRIMARY KEY,
    Name VARCHAR2(100)
);
```

```sql

CREATE TABLE Doctor (
    ID NUMBER PRIMARY KEY,
    Name VARCHAR2(100),
    Salary NUMBER,
    Employed_Date DATE,
    Age NUMBER,
    Dep_ID NUMBER,
    CONSTRAINT fk_dep FOREIGN KEY (Dep_ID) REFERENCES Dep(ID)
);
```

---

# M:N

```sql
CREATE TABLE Project (
    ID NUMBER PRIMARY KEY,
    Name VARCHAR2(100)
);
```

```sql
CREATE TABLE Employee (
    ID NUMBER PRIMARY KEY,
    Name VARCHAR2(100),
    Age NUMBER,
    Loc VARCHAR2(100),
    Status VARCHAR2(50)
);
```

```sql
CREATE TABLE Proj_Emp (
    Proj_ID NUMBER,
    Emp_ID NUMBER,
    CONSTRAINT pk_proj_emp PRIMARY KEY (Proj_ID, Emp_ID),
    CONSTRAINT fk_proj FOREIGN KEY (Proj_ID) REFERENCES Project(ID),
    CONSTRAINT fk_emp FOREIGN KEY (Emp_ID) REFERENCES Employee(ID)
);
```
