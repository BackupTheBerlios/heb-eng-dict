# 
#
# changes
# 01/09/04 - changed "word" into "entry"
# rebuilt!
# 

DROP DATABASE IF EXISTS heb_dict;

CREATE DATABASE heb_dict;
USE heb_dict;

#
# Table structure for table translations
#

CREATE TABLE translations (
  trans_id int(6) unsigned NOT NULL PRIMARY KEY auto_increment,
  lang_id varchar(4) default NULL,
  trans varchar(255) default NULL,
  part_of_speech enum('noun','verb','pronoun','preposition','adjective','adverb') default NULL,
  gender enum('male','female','neuter') default NULL,
  entry_id int(6) NOT NULL default '0',
);



#
# Table structure for table entries
#

CREATE TABLE entries (
  entry_id int(10) unsigned NOT NULL PRIMARY KEY auto_increment,
  entry varchar(255) default NULL,
);


