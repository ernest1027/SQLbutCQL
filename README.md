# SQLbutCQL

A database made from scratch using C that mimics some of the features of SQLite implemented using a B+ tree data structure. Inspired by https://cstack.github.io/db_tutorial/ with additional features added.

### How to use
1) Clone or download the repository
2) Open a terminal at the file location
3) Run the command 'make all'
4) Run the command './main test.db' where test.db can be replaced with the name of your database file.
5) Play around with the SQLbutCQL REPL

### Current available commands
- `insert ID_NUMBER NAME EMAIL`
    - Inserts a row into the table
    - Example: `insert 1 person1 person1@mail.com`
- `select`
    - Displays all rows
- `.exit`
    - Exits the program and saves all inserts to disk. This command must be used for inserts to be saved and persisted on disk.
- `.tree` 
    - Displays the b+ tree data structure

### To be implemented
- Search/select by id
- Creating new tables 
- Introducing custom schema
- Primary/foreign keys
