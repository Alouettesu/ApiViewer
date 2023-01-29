BEGIN TRANSACTION;
CREATE TABLE IF NOT EXISTS `elements` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`api_id`	INTEGER NOT NULL,
	`method`	TEXT NOT NULL,
	`url`	TEXT NOT NULL,
	FOREIGN KEY(`api_id`) REFERENCES `apis`(`id`)
);
CREATE TABLE IF NOT EXISTS `comments` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`request`	TEXT NOT NULL,
	`comment`	TEXT NOT NULL
);
CREATE TABLE IF NOT EXISTS `apis` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
	`url`	TEXT NOT NULL,
	`name`	TEXT NOT NULL,
	`description`	TEXT
);
COMMIT;
