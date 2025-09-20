## Creating the Tables

```sql
CREATE TABLE Subjects (
    ID NUMBER PRIMARY KEY,
    Subject_Name VARCHAR2(100) NOT NULL
);
```

```sql
CREATE TABLE Teachers (
    ID NUMBER PRIMARY KEY,
    Name VARCHAR2(100) NOT NULL,
    Email VARCHAR2(100),
    Phone_Number VARCHAR2(20),
    Subject_ID NUMBER,
    CONSTRAINT fk_subject FOREIGN KEY (Subject_ID) REFERENCES Subjects(ID)
);
```

## Insertion

```sql
INSERT INTO Subjects (ID, Subject_Name) VALUES (1, 'Math');
INSERT INTO Subjects (ID, Subject_Name) VALUES (2, 'Physics');
INSERT INTO Subjects (ID, Subject_Name) VALUES (3, 'Chemistry');
INSERT INTO Subjects (ID, Subject_Name) VALUES (4, 'Biology');
INSERT INTO Subjects (ID, Subject_Name) VALUES (5, 'English');
```

```sql
INSERT INTO Teachers (ID, Name, Email, Phone_Number, Subject_ID) VALUES (1, 'Ali Al-Hakimi', 'ali.hakimi@edu.ye', '770111111', 1);
INSERT INTO Teachers (ID, Name, Email, Phone_Number, Subject_ID) VALUES (2, 'Fatima Al-Sabahi', 'fatima.sabahi@edu.ye', '770222222', 1);
INSERT INTO Teachers (ID, Name, Email, Phone_Number, Subject_ID) VALUES (3, 'Hassan Al-Mahdi', 'hassan.mahdi@edu.ye', '770333333', 2);
INSERT INTO Teachers (ID, Name, Email, Phone_Number, Subject_ID) VALUES (4, 'Nadia Al-Qadi', 'nadia.qadi@edu.ye', '770444444', 3);
INSERT INTO Teachers (ID, Name, Email, Phone_Number, Subject_ID) VALUES (5, 'Sami Al-Ahmar', 'sami.ahmar@edu.ye', '770555555', 4);
```

## Queries

```sql
SELECT * FROM Teachers;

-- ---
-- ||| ID | Name             | Email                   | Phone_Number | Subject_ID |||
-- ||| 1  | Ali Al-Hakimi    | ali.hakimi@edu.ye      | 770111111    | 1          |||
-- ||| 2  | Fatima Al-Sabahi | fatima.sabahi@edu.ye   | 770222222    | 1          |||
-- ||| 3  | Hassan Al-Mahdi  | hassan.mahdi@edu.ye    | 770333333    | 2          |||
-- ||| 4  | Nadia Al-Qadi    | nadia.qadi@edu.ye      | 770444444    | 3          |||
-- ||| 5  | Sami Al-Ahmar    | sami.ahmar@edu.ye      | 770555555    | 4          |||
-- ---
```

```sql

SELECT * FROM Subjects;
-- ---
-- ||| ID | Subject_Name |||
-- ||| 1  | Math         |||
-- ||| 2  | Physics      |||
-- ||| 3  | Chemistry    |||
-- ||| 4  | Biology      |||
-- ||| 5  | English      |||
-- ---
```

```sql
SELECT t.Name, t.Phone_Number, s.Subject_Name
FROM Teachers t
JOIN Subjects s ON t.Subject_ID = s.ID;
-- ---
-- ||| Name             | Phone_Number | Subject_Name |||
-- ||| Ali Al-Hakimi    | 770111111    | Math         |||
-- ||| Fatima Al-Sabahi | 770222222    | Math         |||
-- ||| Hassan Al-Mahdi  | 770333333    | Physics      |||
-- ||| Nadia Al-Qadi    | 770444444    | Chemistry    |||
-- ||| Sami Al-Ahmar    | 770555555    | Biology      |||
-- ---
```

## What Would Happen?

- 1

```sql
ORA-02291: integrity constraint (FK_SUBJECT) violated - parent key not found
```

- 2

```sql
ORA-02449: unique/primary keys in table referenced by foreign keys
```
