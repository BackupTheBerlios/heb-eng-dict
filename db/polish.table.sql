
CREATE TABLE polish ( word_id INTEGER PRIMARY KEY,
	polish varchar(255) NOT NULL default '',
	naked varchar(255) default NULL,
	english varchar(255) default NULL,
	french varchar(255) default NULL,
	hebrew varchar(255) default NULL,
	source varchar(10) NOT NULL default '',
	voice_file varchar(255) default NULL,
	part_of_speech varchar(255) default NULL,  /* enum('verb','noun','pronoun','adjective','adverb','preposition','abbr','figurative','ordinal','exclamation'), */
	category varchar(255) default NULL,
	gender varchar(10) default NULL,  /* enum('male','female','neuter') */
	usa_uk NOT NULL default 'usa' /* enum('usa','uk') */
)



INSERT INTO polish (polish,naked,english,french,hebrew,source,voice_file,part_of_speech,category,gender,usa_uk)
SELECT DISTINCT polish,naked,english,french,hebrew,source,voice_file,part_of_speech,category,gender,usa_uk 
FROM polish2;


/*
INSERT INTO polish2 
SELECT DISTINCT polish,naked,english,french,hebrew,source,voice_file,part_of_speech,category,gender,usa_uk FROM polish;

.output disall.txt
SELECT polish,naked,english,french,hebrew,source,voice_file,part_of_speech,category,gender,usa_uk FROM polish;

INSERT INTO polish 
(polish, naked, english, french, hebrew, source, voice_file, part_of_speech, category, usa_uk) SELECT 
polish, naked, english, french, hebrew, source, voice_file, part_of_speech, category, usa_uk 
FROM newpolish
*/

