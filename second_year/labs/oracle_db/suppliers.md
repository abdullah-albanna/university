## The Table

```sql
CREATE TABLE suppliers (
    id INT PRIMARY KEY,
    name VARCHAR2(100) NOT NULL,
    salary INT,
    status VARCHAR2(100) DEFAULT 'male',
    city VARCHAR2(50),
    specialty VARCHAR2(50)
);
```

## Queries

```sql
SELECT * FROM suppliers;
```

```sql
SELECT name, salary FROM suppliers;
```

```sql
SELECT name AS supplier_name FROM suppliers;
```

```sql
SELECT name || ' ' || city AS full_info FROM suppliers;
```

```sql
SELECT * FROM suppliers WHERE salary > 500;
```

```sql
SELECT * FROM suppliers WHERE salary BETWEEN 400 AND 800;
```

```sql
SELECT * FROM suppliers WHERE status = 'female';
```

```sql
SELECT * FROM suppliers WHERE city IN ('Sana''a', 'Aden');
```

```sql
SELECT * FROM suppliers WHERE name LIKE 'A%';
```

```sql
SELECT * FROM suppliers WHERE salary IS NULL;
```

```sql
SELECT * FROM suppliers WHERE salary > 500 AND status = 'male';
```

```sql
SELECT * FROM suppliers WHERE salary < 600 OR city = 'Taiz';
```

```sql
SELECT * FROM suppliers WHERE salary != 500;
```

```sql
SELECT * FROM suppliers WHERE city != 'Sana''a';
```

```sql
SELECT * FROM suppliers WHERE name IN ('Ali', 'Sara');
```

```sql
SELECT * FROM suppliers WHERE salary BETWEEN 400 AND 700;
```

```sql
SELECT * FROM suppliers WHERE name LIKE '%a%';
```

```sql
SELECT name, salary + 100 AS new_salary FROM suppliers;
```

```sql
SELECT * FROM suppliers ORDER BY salary ASC;
```

```sql
SELECT * FROM suppliers ORDER BY status DESC, name ASC;
```

```sql
SELECT * FROM suppliers WHERE salary IS NULL;
```

```sql
SELECT * FROM suppliers WHERE specialty NOT IN ('IT', 'HR');
```

```sql
SELECT * FROM suppliers WHERE salary NOT BETWEEN 400 AND 600;
```

```sql
SELECT * FROM suppliers WHERE status != 'female';
```

```sql
SELECT * FROM suppliers WHERE name NOT LIKE 'M%';
```
