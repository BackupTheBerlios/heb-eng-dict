# MySQL-Front 3.1  (Build 8.4)


# Host: root    Database: heb_dict
# ------------------------------------------------------
# Server version 4.0.18

DROP DATABASE IF EXISTS `heb_dict`;

CREATE DATABASE `heb_dict`;
USE `heb_dict`;

#
# Table structure for table translations
#

CREATE TABLE `translations` (
  `trans_id` int(6) unsigned NOT NULL auto_increment,
  `trans` varchar(255) default NULL,
  `lang_id` varchar(4) default NULL,
  `word_id` int(6) NOT NULL default '0',
  PRIMARY KEY  (`trans_id`)
) TYPE=MyISAM

#
# Dumping data for table translations
#

INSERT INTO `translations` VALUES (1,'dog','enus',1);
INSERT INTO `translations` VALUES (2,'pot','enus',2);
INSERT INTO `translations` VALUES (3,'to descend','enus',3);
INSERT INTO `translations` VALUES (4,'chien','frfr',1);
INSERT INTO `translations` VALUES (5,'יצור שעיר ונובח (XOR נושך)','heil',1);
INSERT INTO `translations` VALUES (6,'computer','enus',4);
INSERT INTO `translations` VALUES (7,'ordinateur','frfr',4);
INSERT INTO `translations` VALUES (8,'mind','enus',5);
INSERT INTO `translations` VALUES (9,'(he) calculates','enus',6);
INSERT INTO `translations` VALUES (10,'(he) computes','enus',6);

#
# Table structure for table words
#

CREATE TABLE `words` (
  `word_id` int(10) unsigned NOT NULL auto_increment,
  `word` varchar(255) default NULL,
  `part_of_speech` enum('noun','verb','pronoun','preposition','adjective','adverb') default NULL,
  `gender` enum('male','female','neuter') default NULL,
  PRIMARY KEY  (`word_id`)
) TYPE=MyISAM

#
# Dumping data for table words
#

INSERT INTO `words` VALUES (1,'כלב','noun','male');
INSERT INTO `words` VALUES (2,'עציץ','noun','male');
INSERT INTO `words` VALUES (3,'לרדת','verb',NULL);
INSERT INTO `words` VALUES (4,'מחשב','noun','male');
INSERT INTO `words` VALUES (5,'מחשב','noun','male');
INSERT INTO `words` VALUES (6,'מחשב','verb',NULL);

