BEGIN TRANSACTION;
CREATE TABLE `users` (
	`id`	INTEGER PRIMARY KEY AUTOINCREMENT,
	`login`	TEXT,
	`senha`	TEXT
);
INSERT INTO `users` VALUES (1,'admin','admin');
INSERT INTO `users` VALUES (2,'breno','keller');
INSERT INTO `users` VALUES (3,'tiago','carneiro');
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
