BEGIN TRANSACTION;
CREATE TABLE "users" (
	`id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`login`	TEXT,
	`senha`	TEXT,
	`adminLevel`	INTEGER
);
INSERT INTO `users` VALUES (1,'admin','admin',1);
INSERT INTO `users` VALUES (2,'breno','keller',0);
INSERT INTO `users` VALUES (3,'tiago','carneiro',0);
CREATE TABLE "operations" (
	`id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`user_id`	INTEGER,
	`operando1`	REAL,
	`operador`	TEXT,
	`operando2`	REAL,
	`resultado`	REAL,
	FOREIGN KEY(`user_id`) REFERENCES users ( id )
);
COMMIT;
