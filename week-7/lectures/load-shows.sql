
CREATE TABLE shows (
                    id INTEGER,
                    title TEXT NOT NULL,
                    year NUMERIC,
                    episodes INTEGER,
                    PRIMARY KEY(id)
                );
INSERT INTO shows VALUES (1, "The Office", 2008, 100);
INSERT INTO shows VALUES (2, "What We Do in the Shadows", 2018, 30);

CREATE TABLE genres (
                    show_id INTEGER NOT NULL,
                    genre TEXT NOT NULL,
                    FOREIGN KEY(show_id) REFERENCES shows(id)
                );
INSERT INTO genres VALUES (1, "Comedy");
INSERT INTO genres VALUES (2, "Horror");

CREATE TABLE people (
                id INTEGER,
                name TEXT NOT NULL,
                birth NUMERIC,
                PRIMARY KEY(id)
            );
INSERT INTO people VALUES (1, "Steve Carrell", 1970);
INSERT INTO people VALUES (2, "Matt Berry", 1970);
INSERT INTO people VALUES (3, "Office Writer", 1970);
INSERT INTO people VALUES (4, "Shadows Writer", 1970);

CREATE TABLE stars (
                show_id INTEGER NOT NULL,
                person_id INTEGER NOT NULL,
                FOREIGN KEY(show_id) REFERENCES shows(id),
                FOREIGN KEY(person_id) REFERENCES people(id)
            );
INSERT INTO stars VALUES (1, 1);
INSERT INTO stars VALUES (2, 2);

CREATE TABLE writers (
                show_id INTEGER NOT NULL,
                person_id INTEGER NOT NULL,
                FOREIGN KEY(show_id) REFERENCES shows(id),
                FOREIGN KEY(person_id) REFERENCES people(id)
            );
INSERT INTO writers VALUES (1, 3);
INSERT INTO writers VALUES (2, 4);

CREATE TABLE ratings (
                show_id INTEGER NOT NULL,
                rating REAL NOT NULL,
                votes INTEGER NOT NULL,
                FOREIGN KEY(show_id) REFERENCES shows(id)
            );
INSERT INTO ratings VALUES (1, 100, 1000000);
INSERT INTO ratings VALUES (2, 1000, 1000000);
