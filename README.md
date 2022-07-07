# API2019 final project

Implementation of a system to monitor relationships among entities. 

Written in C


# Description

The objective is the impementation of a system to monitor entities and the relationships among them. 

The system must be able to monitor the following phenomenons:
* A new entities begins to be monitored
* A monitored entity stops being monitored
* A new relationship is established between two monitored entities
* A relationship between two monitored entities ceases to exist

Every entity is identified by a name, and the same is true for each type of relatiship. Both types of identifiers are contained within "" and are case sensitive.

Relationships have a direction, they are not necessarely symmetrical.

The program reads from standard input a sequence of commands, each corresponding to a change in an entity or a relationship. When a specific command is received,  a report is created and printed on standard output.

## Commands 
Commands that the progam can receives are:

### • addent ⟨id_ent⟩: 
Adds the entity identified by "id_ent" to the set of monitored entities; if the entity is already being monitor, doesn't do anything. 

### • delent ⟨id_ent⟩: 
Removes the entity identified by "id_ent" from the set of monitored entities; Deletes all the relationship of which "id_ent" is part of (either as origin or destination)

### • addrel ⟨id_orig⟩ ⟨id_dest⟩ ⟨id_rel⟩: 
Adds the relationship identified by "id_rel" between the entities "id_orig" (origin) e "id_dest" (destination). If another relationship with the same identifier already exists between the two entities (with the same direction), or if at least one of the entities is not being monitored, it doesn't do anything. 
Monitoring of the type of relationship identified by "id_rel" implicitely starts with the first addrel regarding that relationship type.

### • delrel ⟨id_orig⟩ ⟨id_dest⟩ ⟨id_rel⟩:
Deletes the relationship identified by "id_rel" between the entities "id_orig" (origin) and "id_dest" (destination); if this relationship doesn't exist, it doesn't do anything

### • report
Produces as output the list of relationships types, reporting for each of them the entity with the largest number of entering connections of that type, together with the number. If more that one entity has the maximum number of entering connections, all of them are returned is ascending order of identifier (ASCII characters ordering) and the number of connections is reported just once at the end. Output structure: ⟨id_rel1⟩ ⟨id_ent1⟩ ⟨n_rel1⟩; ⟨id_rel2⟩ ⟨id_ent2⟩ ⟨id_ent5⟩ ⟨n_rel2⟩; ...

### • end:
Concludes the sequence of commands


Note: The elements composing the commands are separated by spaces. 


## Example

| Input                               | Output                                                                  |
| ----------------------------------- | ----------------------------------------------------------------------- | 
|addent "alice"                       |                                                                         |
|addent "bruno"                       |                                                                         |
|addent "carlo"                       |                                                                         |
|addent "dario"                       |                                                                         |
|report                               |none                                                                     |
|addrel "carlo" "bruno" "friend_with" |                                                                         |
|report                               |"friend_with" "bruno" 1;                                                 |
|addrel "carlo" "alice" "friend_with" |                                                                         |
|report                               |"friend_with" "alice" "bruno" 1;                                         |
|addrel "alice" "bruno" "classmate_of"|                                                                         |
|report                               |"friend_with" "bruno" 2;                                                 |
|addrel "bruno" "dario" "classmate_of"|                                                                         |
|report                               |"friend_with" "bruno" 2; "classmate_of" "dario" 1;                        |
|delrel "carlo" "alice" "friend_with" |                                                                         |
|report                               |"friend_with" "bruno" 2; "classmate_of" "dario" 1;                       |
|addrel "carlo" "alice" "classmate_of"|                                                                         |
|report                               |"friend_with" "bruno" 2; "classmate_of" "alice" "dario" 1;               |
|addrel "carlo" "bruno" "classmate_of"|                                                                         |
|report                               |"friend_with" "bruno" 2; "classmate_of" "alice" "bruno" "dario" 1;       |
|delent "alice"                       |                                                                         |
|report                               |"friend_with" "bruno" 1; "classmate_of" "bruno" "dario" 1;               |
|end                                  |       |                                                                 |

## Constrains
* only standard C language
* only libc can be used


# Tests

A few test samples are publicly available.

Evaluation is based on the performances on a set of hidden tests.

Both suites of tests can be downloaded [here](https://drive.google.com/drive/folders/1Mhsp5mrPm1hzsrmpzb8LkqEu0lgZM7-M?usp=sharing)

# Performances

### Time Performances

| Test Name         | T max [s]     | T completion [s] |
| ----------------- | ------------- | ---------------- |
| Monotone          | 4,320         | 2,530            |
| Dropoff           | 6,963         | 3,211            |
| Mixup             | 0,610         | 0,257            |
| Repeated          | 1,139         | 0,405            |
| MultipleMixUp     | 3,062         | 1,178            |
| MultipleRepeated  | 5,34          | 1,911            |
| Laude             | 1,64          | 1,020            |


### Memory Performances

| Test Name         | M max [MB]   | M required [MB]   |
| ----------------- | ------------ | ----------------- |
| Monotone          | 200          | 176               |
| Dropoff           | 190          | 172               |
| Mixup             | 6            | 5.07              |
| Repeated          | 9            | 7.10              |
| MultipleMixUp     | 20           | 18.50             |
| MultipleRepeated  | 35           | 32.20             |
| Laude             | 23           | 20.60             |
