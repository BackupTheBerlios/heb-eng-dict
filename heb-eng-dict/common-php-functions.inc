<?
/*
	description:
		common php functions
		for dealing with DB,

*/


// ------- globals
$independent_tables_mode = 0;
$CONFIG_DIR = '.';
$DEBUG = 1;
require_once("$CONFIG_DIR/config.inc");





/********************************************************
*
*	guess what is the site
*   to which this uri belongs.

*
********************************************************/




//  --------- print user selection menu -----------
//         "return" the variable $user_id
//
//		5/08/01: addition to be multi_user
//		         thus, $this_user_id is accepted to be 
//               an Array in some cases
//
/*
function print_user_selection($users_table="users",$user_id_field="id",$this_user_id="", $multiple=0, $size=5, $group="" ) 
{

	if($multiple) {
		
		print "<SELECT MULTIPLE SIZE=$size NAME='user_ids[]' STYLE='width:150'>";

		$sql = "SELECT username, $user_id_field FROM $users_table ";
		if ($group) { $sql .= " WHERE organization='$group' "; }
		debug ("user listing: $sql");
		$dbh = sql_query($sql);
		if (!$dbh) { print_error("User list retrieval error."); }

		while ( $row = mysql_fetch_row($dbh) ) {
			$tmp_user = $row[0];
			$tmp_user_id = $row[1];

			print "<OPTION ";
			if( $this_user_id ) { 
				if (in_array($tmp_user_id, $this_user_id) ) { print " SELECTED "; }
			}
			print " VALUE='$tmp_user_id'>$tmp_user</OPTION>\n";
		} 

		$sys_id = get_user_id_from_user_name('system', "users", 0, "user_id");
		print "<OPTION VALUE='$sys_id'>System</OPTION>\n";
		print "</SELECT>";



	}
	else { // ------ single user selection

		print "<SELECT NAME='user_id'>";

		$sql = "SELECT username, $user_id_field FROM $users_table";
		if ($group) { $sql .= " WHERE organization='$group' "; }
		debug("single user: $sql");
		$dbh = sql_query($sql, "user retrieval error.");

		while ( $row = mysql_fetch_row($dbh) ) {
			$tmp_user = $row[0];
			$tmp_user_id = $row[1];

			print "<option ";
			if ($this_user_id == $tmp_user_id) { print " SELECTED "; }
			print " value='$tmp_user_id'>$tmp_user</option>\n";
		 } 
		print "<option ";
		if ($this_user_id == '%') { print " SELECTED "; }
		print "value='%'> all users (long output)</option>\n";
		print "</select>";
	}
}
/*




//
//  --------- print batch selection menu -----------
//         "return" <SLELCT>, 
//         variable $batch_ids
//
function print_x_selection($current_x_ids, $multiple=1, $size=5) {
	
	//print "ZZZZZZZZ<HR><H1>aaaaa</h1>";
	print "<SELECT ";
	if ($multiple)	{ print " MULTIPLE "; }
	if ($size)		{ print " SIZE='$size' "; }
	print "name='x_ids[]'>\n";

	$sql = "SELECT description, x_id FROM xes";
	$dbh = sql_query($sql, "| xes retrieval error.");
	while ( $row = mysql_fetch_array($dbh) ) {
		$desc = $row['description'];
		$id = $row['x_id'];

		print "<option ";
		if($current_x_ids) {if(in_array($id, $current_x_ids)) { print " SELECTED "; }}
		print " VALUE='$id'>$desc</option>\n";
	 } 

	print "</SELECT>";
}





//
//  --------- print x selection menu -----------
//         "return" <SLELCT>, 
//         variable $x_ids
//
function print_selection($selected_value, $multiple=1, $size=5 ) {
	
	//switch
	$table = 'message_catalog';
	$name = 'type';
	$where = '';
	// end switch

	print "<SELECT ";
	if ($multiple)	{ print " MULTIPLE "; }
	if ($size)		{ print " SIZE='$size' "; }
	//print "name='$name[]'>\n";

	$sql = "SELECT * FROM $table $where";
	$dbh = sql_query($sql, "| xes retrieval error.");
	while ( $row = mysql_fetch_array($dbh) ) {
		$val = $row[$val];
		$id = $row[$id];

		print "<option ";
		if($current_x_ids) {if(in_array($id, $current_x_ids)) { print " SELECTED "; }}
		print " VALUE='$id'>$desc</option>\n";
	 } 

	// ---- note: % is for using in SQL query:
	print "</SELECT>";
}
*/


//
// ---- prepare str for SQL:
//      ... WHERE x IN (a, b, c)
//      in the form of "moshe, dany, yosef"
//
function get_sql_list_from_array($arr) {
	$sql = "";
	$i = 0;
	if (isset($arr)) {
		$sql = "";
		$sep = " ";
		foreach( $arr as $tmp_item )  {
			$sql .= $sep . $tmp_item;
			$sep=",";
			++$i;
		}
	}
	return($sql);
}



//
//  send a standard error message
//  
//  optionally stop
//
function error_message($id=0, $halt_on_error=1){

	print "<HTML><BODY>";
	switch ($id) {
		case 0:
			$msg = "<H1>bahaha:</h1>\n<h1><img src='images/wgbh-default.jpg'>";
			print $msg;
			break;
	
		case 1:
			$msg = "";

		default:
			$msg = "<H1>bahaha:</h1>\n";
			print $msg;

	}

	if ($halt_on_error) {
		exit(1);
	}

}




//
//  send a standard error message
//  optionally send url where you want return to
//  
//
function error_message_page($msg, $back_url=""){
	
	$back_url = urlencode($url);
	$msg = urlencode($msg);
	$error_url = "x_error_page.php?msg=$msg&url=$back_url";
}




// -------- nicely end document -------------
//  used in cases we need to terminate,
//  such as in error situations
//
function end_html_document($msg="", $exit=0) {
	$end_html_string = "<!-- end of file --></BODY></HTML>";
	print $msg . "\n" . $end_html_string;

	// stop processing
	if ($exit) { exit; }
}






//
// the caller should supply username.
// if the user is not already in the users table,
// the function adds the new user
//
//  $user_id_fieldname="id"  is for backward compatibility
//
function get_user_id_from_user_name($username, $users_table="users", $insert_if_not_exist=1, $user_id_fieldname="id") {
	
	// chop off redundant spaces
	$username = trim($username);

	//$sql  = "SELECT user_id FROM $users_table WHERE username like '$username'";
	$sql  = "SELECT $user_id_fieldname FROM $users_table WHERE username like '$username'";
	$error_msg = "<!-- problems getting user id.  \n 
		trying to add user to db.\n 
		$sql -->";

	$id = get_single_scalar_from_query($sql);

	//if ($user_id == "") { 
	if ($insert_if_not_exist) {
		if (!$id) { 
			$sql = "INSERT INTO $users_table SET username='$username'";
			//$user_id = sql_insert($sql, "errol!", 1);
			$id = sql_insert($sql, "<h2>errol!</h2> user does not exist!", 1);
		}
	}
	//print "|-|$username|-|";
	//return $user_id;
	return $id;
}





/******************************************************************
	
	return username (string)
	by its user_id

******************************************************************/
function get_username_for_user_id($username, $user_id_fieldname="user_id", $users_table="users") {
	
	// --- chop off redundant spaces 
	$username = trim($username);

	$sql  = "SELECT username FROM $users_table WHERE user_id like '$user_id_fieldname'";
	$username = get_single_scalar_from_query($sql);

	return $username;
}







/**
 * connect to mysql database according to the
 * parameters in config.inc
 */
function connect_to_mysql() {
	global $CONFIG_DIR;
	include "$CONFIG_DIR/config.inc";
	/* hostname for MySQL connection */
	if ( $hostname == "") {
		$hostname = "localhost";
	}
	mysql_connect($hostname, $username, $password) 
		or die("Unable to connect to database:". mysql_error());
	mysql_select_db($database) 
		or die("Can't select $database:". mysql_error());
}



/* ----------- standard query 
               and error checking 
			   for SQL connection ------- */

function sql_query($tmp_sql, $msg="", $halt_on_error=1) {

	// print "<BR>\n!!$tmp_sql!! \n<br>";

	$dbh = mysql_query($tmp_sql);
	if (!$dbh) { 
		if ($halt_on_error) {
			print "<!-- ";
			print mysql_error();
			print "\n Offender sql query: >>>";
			print $tmp_sql ." <<<\n";
			print " -->";
			print $msg ."\n";
			exit(1);
		}
	}

	return $dbh;
}




	







// -------------------------------------------------------
//
//	return the first piece of data 
//  from the first rows 
//  of a sql statemtnet
//
//  (used, among other things, to get Count of results)
//
function get_single_scalar_from_query($sql) {
	$dbh = sql_query($sql);
	$row = mysql_fetch_row($dbh);
	return $row[0];
}


//
//
//  performs an INSERT command, 
//  return the last insert id
//  return -1 if failed
//
function sql_insert($sql, $msg="", $halt_on_error=1) {

	$dbh = sql_query($sql, $msg, $halt_on_error);
	if ($dbh) {
		$id = mysql_insert_id ();
		return $id;
	}

	else {
		return (-1);
	}

} // end func








// -------------------------------------------------------
//
//	return the first piece of data 
//  from the first rows 
//  of a sql statemtnet
//
//  (used, among other things, to get Count of soething)
//
function debug($msg) {
	global $DEBUG, $CONFIG_DIR;
	include "$CONFIG_DIR/config.inc";
	if( $DEBUG ) { 
		print "[$msg]<br>\n"; 
		flush();
	}
}






 



//
// print standard x logo. 
// consider its background.
//
// NOTE: png transparency is badly implemented on IE
//
function print_x_logo($size="big", $backcolor='white', $url="") {	
	if(!$url) { 
		include "$CONFIG_DIR/config.inc";
		$url=$x_HOMEPAGE; 
	}

	?><a 
		href="<? print $url; ?>"

	><img 
		src="<? print "images/x-logo-$size-$backcolor.gif"; ?>"
		border="0"></a><?
}



// standard x header 
//
//
function print_header_new($title, $subtitle="", $url="", $size="normal", $image_bgcolor="white") {	
	
	switch($size) {
		case "large":
		case "big":
			$width="100%";
			$hr="<hr width='70%' height=1>\n";
			break;
		case "small":
			$width="300";
			$hr="<BR>\n";
			break;
		case "normal":
			$width='70%';
			$hr="<hr width='70%' height=1>\n";
			break;
		default:
			$width="100%";
			$hr="<hr width='70%' height=1>\n";
	}
	?>
	<table 
		border=0 
		cellspacing=3 cellpadding=3 
		width="<? print $width; ?>"><tr>
		
		<!-- logo -->
		<td width="10%" valign=middle align=left>
			<? print_x_logo($size, $image_bgcolor, $url); ?>
		</td>

		<!-- titles -->
		<TD ALIGN=center VALIGN=middle WIDTH='90%'>
			<FONT SIZE='+1'><B><? print $title; ?></B></FONT>
			<?	print $hr; print $subtitle; ?>
		</td></tr>

	</table>
	<!--/div-->
	<? 
} 





//-- to be finished --
//
//
function print_logo() {
	?>
	<table border=0 cellspacing=0 cellpadding=0><tr>
		<td><a 
			href="http://related.tv/"
			TARGET="_parent"
			
			><img src="images/x-logo_turning-on-itv.png" 
			border="0"></a>
		</td></tr>
	</table>
	<? 
} 


//-- --------- x's search - standard footer --------------- --
//
//
function print_footer($jobs=1, $help="") { 

	if (!$result_line_size) { $result_line_size = "60%";}
	if ($result_line_size < 200) {$result_line_size = "60%";}
	?> 


	<center>
	<table width=<? print $result_line_size; ?> border=0 cellspacing=0 cellpadding=0>

		<tr><td align=center bgcolor='#CCFFFF'>
			<font class=head2>
				<a href="http://www.x.com">About</a> | 
				<a href="mailto:contact@x.com">Contact</a> 
				<? if($jobs) { print " | <a href='mailto:jobs@x.com'>Jobs</a>"; } ?>
				<? if($help!="") { print " | <a href='$help'>How to use</a>"; } ?>
			</font>
		</td></tr>
		<tr><td align=center>
			<font class=body1 size=-1>Copyright (C) 2001, x Inc.</font>
		</td></tr>
	</table>

	</center>
<? } 









//
// function id_2_path - build path and create file name from a given number 
// this function gets an id from the database and returns 
// the directory to store a file and the file name (without the end (like .html))
// the output is in array [0] = direstory [1] = filename
// assume 8 chars hirercy
//
//   look at id_2_path_create:  
//   it actually creates the path 
//
//
function id_2_path($id, $mkdir=0, $base=""){

	$padd = str_pad($id, 8, "0", STR_PAD_LEFT); 

	// - d1/d2/d3 - like 00/0000/000000
	$d1 = substr($padd,1,2);
	$d2 = substr($padd,1,4);
	$d3 = substr($padd,1,6);

	$file_name = $padd;
	$dir = "$d1/$d2/$d3";
	$ret_arr[0] = $dir;
	$ret_arr[1] = $file_name;

	return $ret_arr;
}



//
// function id_2_path - build path and create file name from a given number 
// this function gets an id from the database and returns 
// the directory to store a file and the file name (without the end (like .html))
// the output is in array [0] = direstory [1] = filename
// assume 8 chars hirercy
//
//   added mkdir option, to create this path in the 
//
//
function id_2_path_and_create($id, $base="", $sep="/", $extension=""){

	$padd = str_pad($id, 8, "0", STR_PAD_LEFT); 
	// - d1/d2/d3 - like 00/0000/000000
	$d1 = substr($padd,0,2);
	$d2 = substr($padd,0,4);
	$d3 = substr($padd,0,6);

	$dir="$base$sep$d1"; if (!file_exists($dir)) { mkdir ($dir,0777); }
	$dir="$base$sep$d1$sep$d2"; if (!file_exists($dir)) { mkdir ($dir,0777); }
	$dir="$base$sep$d1$sep$d2$sep$d3"; if (!file_exists($dir)) { mkdir ($dir,0777); }

	$file_name = $padd . $extension;
	$dir = "$d1$sep$d2$sep$d3";
	$ret_arr[0] = $dir;
	$ret_arr[1] = $file_name;

	return $ret_arr;
}



//
// function send_tcp_message - Sends a TCP/IP message. 
//
function send_tcp_message($message, $address, $port){
	/* Get the port for the WWW service. */
	if ($port == ''){
		$port = getservbyname ('www', 'tcp');
	}
	/* Get the IP address for the target host. */
	if ($address == ''){
		$address = gethostbyname ('compy');
	}

	/* Create a TCP/IP socket. */
	$socket = socket (AF_INET, SOCK_STREAM, 0);
	if ($socket < 0) {
		echo "socket() failed: reason: " . strerror ($socket) . "\n";
		return;
	}
	$result = connect ($socket, $address, $port);
	if ($result < 0) {
		echo "connect() to ".$address.":".$port."failed. Reason: ($result) " . strerror($result) . "\n";
		return;
	}
	write ($socket, $message, strlen($message));
	close ($socket);
}



//
//    use this in the header of your HTML
//
function print_charset_meta_tag($charset='UTF-8') {
	
	"<meta HTTP-EQUIV='Content-Type' CONTENT='text/html; charset='$charset'>";
}



//
//    get type id
//    from "content_type"s table
//    (create entry if not exist)
//
function get_mime_type_id($content_type, $insert_if_not_exist=1, $table='content_types') {

	// chop off redundant spaces
	$content_type = trim($content_type);
	$sql  = "SELECT content_type_id FROM $table WHERE content_type like '$content_type'";
	$error_msg = "<!-- problems getting content_type id. \n $sql -->";

	//$user_id = get_single_scalar_from_query($sql);
	$id = get_single_scalar_from_query($sql);

	//  if no content_type found 
	if ($insert_if_not_exist) {
		if ($id == "") { 
			$sql = "INSERT INTO $table SET content_type='$content_type'";
			$id = sql_insert($sql, "errol!", 1);
		}
	}

	return $id;
}



//
//
//   fet date good for MySQL datetime
//
//
function get_datetime($what_date="") {
	if ($what_date = "") {
		$date = date("Y-n-j H:i:s");
	}

	else {
		$date = date("Y-n-j H:i:s", $what_date);
	}
	return $date;
}









/***************************************************************
		get a file from the internet
		up to max_size bytes
		return: locally saved (tmp) filename


****************************************************************/
function retrieve_url($url, $progress_indicator=1, $max_size=2000000) {

	if ($progress_indicator) { 
		print "<Font size=1>Please wait while loading $url...</font>\n"; 
		flush();
	}

	/*error_reporting(1);
	$fp = fopen ($url, "r");
	if (!$fp) {
		if ($progress_indicator) { 	print "Failed opening <b>$url</b>.<br>"; }
		return $fp;
	}

	$s = fread($fp, 2000000);
	fclose($fp);
	*/

	$escaped_url = $url; //$escaped_url = escapeshellcmd($url);
	$tmpfname = tempnam("/tmp", "catman_url_");
	//$cmd = "wget -O - '$escaped_url' > $tmpfname";
	$cmd = "TMPDIR=/tmp /usr/bin/lynx -source '$escaped_url' > $tmpfname";	
	$retval=0;
	$out = system($cmd, $retval);
	if ($retval == 0) { $retval = $tmpfname; }
	return $retval;
}



/*
 *
 *	returns a url that bypass authenticaion etc
 *   filters available: nytimes
 *
 */
function normalize_url($url) {

	$new_url = $url;  // default
	
	// ---- check for nytimes
	$nytimes = "www.nytimes.com";
	if (stristr($url, $nytimes))  { 

		$username='newsagent0';
		$password='nytpass';

		$new_url = "http://www.nytimes.com/auth/chk_login?is_continue=true&URI=". $url ."&OQ=&USERID=". $username ."&PASSWORD=". $password ."&SAVEOPTION=YES";
	}


	return $new_url;
}







//
//
//	returns a negative answer: given 1, return 0
//
function not($x) { 
	if($x)	{return 0;} 
	else	{return 1;}
}












/***********************************************************************
 *
 *	save <source> as <target>
 *  after proccessing thru filter based on <source>
 *
 *  default target is the source itself
 *  you should worry about file & dir permissions, & existance
 *
 */
function filter_file($source_id, $original_file, $target_filename="", $url="", $get_pictures_only=0) {

	$source = get_source_from_source_id($source_id);
	$url = trim($url);
	$source = strtolower($source);
	$source = str_replace("_", " ", $source);
	debug("in filter: pics? = $get_pictures_only");

	include "$CONFIG_DIR/config.inc";

	// default target filename is: source-file-name.filtered
	if($target_filename=="") { 
		$target_filename = "$original_file.filtered"; 
	}
	


	switch($source) {
		case "washington times":
			break;

		case "la times":
		case "la times2doc":
			break;

		case "independent":
		case "independent2doc":
			break;

		case "telegraph":
			break;

		case "de telegraaf":
		case "telegraaf":
			break;

		case "ny post":
		case "ny post2doc":
			break;

		case "new york times":
		case "nyt":
		case "nytimes":
		case "ny times":
		case "nytimes2doc":
			/*
			nytimes2article.pl 
			-i | --input 	 input html file. default : STDIN.
			-l | --lexicon   filename of the LEXICON. deafult: ./lexicon.img
			-c | --calc_sigs filename of the calc_sigs program. default: ./calc_sigs
			-o | --output   filename of where output will be placed. defalut:STDOUT.
			-I | --ID  ID number of the given file. default: 1 
			-U | --URL    URL of the origin of the given file.	If ommited - ignored!
			-t | --title_weight  the weight of the title (int). default 1.
			-a | --allsigs
					show signatures for all parts (whole article, title, paragraphs, sentences). 	If ommited, no signatures are calculated.
			-p | --pictures   print full url of "good" pictures. override other parameters
			*/
			
			if ($get_pictures_only) { $params = "--pictures"; }

			else { 
				$params = " --lexicon='$lexfile' --calc_sigs='@@CONFIG-BINDIR@@/calc_sigs'";
				$params = ""; // debug! above is needed if summarizer knows how to use sigs in xml-doc
				if (strlen($url)>1) {$params .= " --URL='$url' ";}
			}
			$cmd = "cat '$original_file' | @@CONFIG-BINDIR@@/nytimes2article.pl $params > '$target_filename'";

			break;




		case "financial times":
			break;

		case "usa today":
		case "usa today2doc":
			break;


		case "jerusalem post":
		case "jpost":
			/*
			jpost2article.pl [-i filename] [-l filename] [-c filename] [-o filename] [-I id] [-U url] [-t weight] [--allsigs] [--noisy] [--help]
			*/
			if ($get_pictures_only) { $params = "--pictures"; }
			else { 
				// --lexicon='$lexfile' --calc_sigs='@@CONFIG-BINDIR@@/calc_sigs'
				if (strlen($url)>1) {$params = " --URL='$url' ";}
			}
			$cmd = "cat '$original_file' | @@CONFIG-BINDIR@@/jpost2article.pl $params > '$target_filename'";
			break;

		case "us info":
		case "us info2doc":
			break;


		case "washington post - technology":
		case "washtech":
			if ($get_pictures_only) { $params = "--pictures"; }
			else { 
				// --lexicon='$lexfile' --calc_sigs='@@CONFIG-BINDIR@@/calc_sigs'
				if (strlen($url)>1) {$params = " --URL='$url' ";}
			}
			$cmd = "cat '$original_file' | @@CONFIG-BINDIR@@/washtech2article.pl $params > '$target_filename'";
			break;




		case "washington post":
		case "wpost2doc":
			/*
	        wpostsports2article.pl [-i filename] [-l filename] [-c filename] [-o filename]
                [-I id] [-U url] [-t weight] [--allsigs] [--pictures]
			-i | --input	html filename containing a wpost article. default STDIN
			-l | --lexicon	 filename of the LEXICON.  default ./lexicon.img 
			-c | --calc_sigs	   filename of calc_sigs program.  default: ./calc_sigs
			-o | --output   filename output file.  default: STDOUT.
			-I | --ID	id of given file. positive integer.	deafult: 1
			-U | --URL	URL of the origin of the given file. If ommited - ignored!
			-t | --title_weight   A positive number suggesting the weight of the title.  default: 1, as the weight of the title.
			-a | --allsigs   show signatures for all parts (whole article, title, paragraphs, sentences). default: no signatures calculated.
			-p | --pictures  print full url of "good" pictures. override other parameters
			*/
			if ($get_pictures_only) { $params = "--pictures"; }
			else { 
				// --lexicon='$lexfile' --calc_sigs='@@CONFIG-BINDIR@@/calc_sigs'
				if (strlen($url)>1) {$params = " --URL='$url' ";}
			}
			$cmd = "cat '$original_file' | @@CONFIG-BINDIR@@/wpostsports2article.pl $params > '$target_filename'";
			break;



		case "oglobo":
		case "oglobo2doc":
			/*
				--input=
					input=fileslist:  get a list of files to work on, from STDIN
					input=html:       expect to get from STDIN, the HTML of a single page
				--format=plaintext
					strip all tags and bullshit, gives ONLY text.
				--format=doc (default behaviour)
					add "<DOC> ... </DOC>" notation.
				--removejunk
					delete all known oglobo junk words
				--removetags
					try to remove html tags with its own tools
			*/
			if ($get_pictures_only) { $params = "--pictures"; }
			else { $params = ""; }
			$cmd = "@@CONFIG-BINDIR@@/oglobo2article.pl --input='$original_file' --output='$target_filename'";
			break;


	
		case "html2plain text":
			$cmd = "cat $original_file | @@CONFIG-BINDIR@@/html2plain_text.py --input=html --removetags > $target_filename";
			break;


		case "html2doc":
		default:

			if($get_pictures_only) {
				// not handling imagfes in this filter yet!
				return;
			}
				
			// --output='$target_filename' 
			if (strlen($url)>1) {$params_url = " --URL='$url' ";}
			$cmd = "@@CONFIG-BINDIR@@/html2article.pl --input='$original_file' --lexicon='$lexfile' --calc_sigs='@@CONFIG-BINDIR@@/calc_sigs' $params_url > $target_filename";

	} // end of switch(filter)



	debug("filter cmd: $cmd");
	$ret = system($cmd, $retval);
	if ($retval) { 
		$retval = 0; 
	}
	else {
		$retval = $target_filename;
	}

	return $retval;

} // end of function filter-file










/***************************************
 *
 *	
 *  standard background image
 *  taken per user
 *
 *
 */
function print_background_image($username="") {
	global $CONFIG_DIR;
	include "$CONFIG_DIR/config.inc";
	
	if (!connect_to_mysql()) {return;}
	global $REMOTE_USER;

	// default is current
	if ($username=="") { $username=$REMOTE_USER; }

	if (!  $user_id = get_user_id_from_user_name($username, "users", 1, "user_id") ) {return;}
	$sql = "SELECT background_id FROM users WHERE user_id=$user_id";
	if (!  $i = get_single_scalar_from_query($sql) ) {return;}
	$src = "images/x-background-$i";

	print $src;
}




function print_records_per_page($username, $lines_per_page=7) {
	
	print "<select onChange=\"location.href='$PHP_SELF?userlines='+document.all.userlines.value\" name=userlines>";
	
	$sql = "UPDATE users SET records_per_page=$lines_per_page WHERE username='$username'";
	sql_query($sql);

	if($lines_per_page==5) {$s='SELECTED';}else{$s="";}
	print"<option $s value=5>5";
	if($lines_per_page==7) {$s='SELECTED';}else{$s="";}
	print"<option $s value=7>7";
	if($lines_per_page==10) {$s='SELECTED';}else{$s="";}
	print"<option $s value=10>10";
	if($lines_per_page==20) {$s='SELECTED';}else{$s="";}
	print"<option $s value=20>20";
	if($lines_per_page==30) {$s='SELECTED';}else{$s="";}
	print"<option $s value=30>30";
	if($lines_per_page>100) {$s='SELECTED';}else{$s="";}
	print"<option $s value=200>all</select>";

}




/**************************************************
 *
 *	
 *  date selection
 *  returns date (day/month/year)
 *
 *  code generated: 
 *    user_date_day
 *    user_date_month
 *    user_date_year
 *
 */
function print_date_selection($basename='user_date', $date_sep="-", $day_id=0, $month_id=0, $year_id=0) {

	include_once("$CONFIG_DIR/xLangDef.php");
	$month_names = Array('?', _JAN, _FEB, _MAR, _APR, _MAY, _JUN, 
						 _JUL, _AUG, _SEP, _OCT, _NOV, _DEC);


	$d = getdate();
	if(!$day_id)   { $day_id   = $d['mday'];}
	if(!$month_id) { $month_id = $d['mon'];}
	if(!$year_id)  { $year_id  = $d['year'];}
	if(!$to_year)  { $to_year  = $d['year'] + 1;}

	// --- day ---
	print "<SELECT xInput NAME='${basename}_day' class=xInput>";
	for($i=1; $i<=31; $i++) { 
		print "<option ";
		if ($day_id == $i) { print " SELECTED "; }
		print " value='$i'>$i</option>\n";
	}
	print "</select>";
	print $date_sep;

	// --- month ---
	print "<SELECT NAME='${basename}_month' class=xInput>";
	for($i=1; $i<=12; $i++) { 
		$month_name = $month_names[$i];
		print "<option ";
		if ($month_id == $i) { print " SELECTED "; }
		print " value='$i'>$month_name</option>\n";
	}
	print "</select>";
	print $date_sep;

	// --- year ---
	print "<SELECT NAME='${basename}_year' class=xInput>";
	for($i=1950; $i<$to_year; $i++) { 
		print "<option ";
		if ($year_id == $i) { print " SELECTED "; }
		print " value='$i'>$i</option>\n";
	}
	print "</select>";
}




/**************************************************
 *
 *	
 *  date selection
 *
 *
 */
function print_chart($data, $image, $width, $height, $table_title="", $border=0, $hide_title=0) {

	$padding = 2;

	/*
		$data['q4'] = 250;
		$data['q1'] = 150;
		$data['ashi'] = 350;
		$data['zoro'] = 50;
		$data['poco'] = 150;
	*/


	// get maximum
	$x_max = count($data);
	$y_max = 400;
	$x_min = 0;
	$y_min = 0;
	foreach ($data as $key => $value) {	
		$y_max = max($y_max, $value); 
		$y_min = min($y_min, $value); 
	}
	reset($data);
	$bar_width  = $width / ($x_max + $padding);

	?>
	<TABLE border=1>
	<TR>
		<TD>&nbsp;</TD>
		<TD align=center><B><? print $table_title; ?></b></TD>
	</TR>

	
	<TR>

		<TD valign=top>
			<?
			print "<TABLE height='$height' border=0 cellpadding=0 cellspacing=0>
				<TR><TD height=50% valign=top    align=right>$y_max</TD></tr>
				<tr><TD height=50% valign=bottom align=right>$y_min</TD></TR>
				</TABLE>\n";
			?>
		</TD>


		<TD>
			<img src="images/spacer.gif" height=1 width=<? print $width; ?>><BR>
			<TABLE width='<? print $width; ?>'>
				<TR>
					<?
					$tit = "";
					foreach ($data as $key => $value) {
						$h = $height * ($value/$y_max);
						$w = $bar_width;
						if ($hide_title) { $tit = "TITLE='$key'"; }
						print "<TD align=center valign=bottom><img src='$image' $tit border=$border width='$w' height='$h'></td>\n";
					}
					reset($data)
					?>
				</TR>

				<?
				if (!$hide_title) { 
				
					print "<TR>\n";
					foreach ($data as $key => $value) { 
						print "<TD align=center><font size='-2'>$key</font></td>"; 
					}
					reset($data);
					print "</TR>\n";
				}
				?>
			</TABLE>
	
		</TD>
	</TR>
	</TABLE>	
	<?
}







function print_grade_selection( $cat_id, $previously_selected_grade=2 ) {
	$selected[$previously_selected_grade+2] = "SELECTED";
	
	$s = "\n\n<SELECT name='selected_grades[$cat_id]'>\n";
	$s .= "\t<OPTION value='-2' " . $selected[0] . ">-2</option>\n";
	$s .= "\t<OPTION value='-1' " . $selected[1] . ">-1</option>\n";
	$s .= "\t<OPTION value= '0' " . $selected[2]  . "> 0</option>\n";
	$s .= "\t<OPTION value= '1' " . $selected[3]  . ">+1</option>\n";
	$s .= "\t<OPTION value= '2' " . $selected[4]  . ">+2</option>\n";
	$s .= "</SELECT>\n";
	return $s;
}









/*
   ------ only some users allowed to come in: ----------

	:todo:
	there are already tables in the SQL db.
	just need to implemet them, in this function

*/
function has_permission($username, $permission) {
	//print "was in permissions: here <BR>\n";

	connect_to_mysql();
	switch($permission) {

		case "misc utilities":
			$sql = "SELECT organization FROM users WHERE username='$username' AND organization='x'";
			$ret = sql_query($sql);
			$affected = mysql_affected_rows();
			//print " ret:|$ret|  sql:|$sql| affected: |$affected|";
			if($affected < 1) { return 0; }
			else { return 1; }
			break;
		
		case "update_status":
			$allowed_users = array('michal', 'yoni');
			if(in_array($username, $allowed_users)) { return 1; }
			else { return 0; }
			break;
		
		case "test site":
			$allowed_users = array('michal', 'koko');
			if(in_array($username, $allowed_users)) { return 1; }
			else { return 0; }
			break;


		case "see other users categorization":
			/*
			$sql = "SELECT organization FROM users WHERE username='$username' AND organization='x'";
			$ret = sql_query($sql);
			$affected = mysql_affected_rows();
			if($affected < 1) { return 0; }
			else { return 1; }
			*/
			return 1;
			break;
		

		case "calculate signatures":
		case "administrator":
			$allowed_users = array('momo','koko');
			if(in_array($username, $allowed_users)) { return 1; }
			else { return 0; }
			break;

		
		case "client_administrator":
			$allowed_users = array('momo','koko', 'asaf');
			if(in_array($username, $allowed_users)) { return 1; }
			else { return 0; }
			break;

		
		default:
			return 0;
	}
}









/************************************************************
*
*	prints all html 
*   & x's standard headers
*	
*   comes hand in hand with 'print_full_footer'
*   $show_border is for debugging mode
*
*
*   if $independent_tables is true,  then there is no one big table.
*   this allows to do 'flush()' in the body part.
*
************************************************************/
function print_full_header($html_title="", $page_title="", $url, $size="normal", $image_bgcolor="white", $meta_tags="", $show_border_for_debug=0) {

	global $independent_tables_mode;

	switch($size) {
		case "big":
		case "large":
			$header_width = '70%';
			break;
		case "small":
			$header_width = '100%';
			break;
		case "normal":
		default:
			$header_width = '70%';
	}


	$header_height = "";

	if ($independent_tables_mode) { 
		$body_properties = "xTOPMARGIN=0 LEFTMARGIN=30 MARGINWIDTH=30 RIGHTMARGIN=30";
		$end_of_header = "</TABLE>";
	} else {
		$body_properties = "TOPMARGIN=0 LEFTMARGIN=0 MARGINWIDTH=0 RIGHTMARGIN=0";
		$header_height = "height='100%'";
		$end_of_header = "<tr><td valign=middle>";
	}



	?><!DOCTYPE html
			PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN"
			"DTD/xhtml1-transitional.dtd">
	<HTML xmlns="http://www.w3.org/1999/xhtml" lang="en-US">

	<!-- ------------------- start of header ------------- -->
		<HEAD>
		<? if(!$meta_tags) { ?>
		<META NAME="HTTP_EQUIV" CONTENT="text/html; charset=ISO-8859-1">
		<? } else { print $meta_tags; } ?>
		<TITLE><? print $html_title; ?></TITLE>
	</HEAD>


	<BODY 
		BACKGROUND="<? print_background_image(); ?>"
		<? print $body_properties; ?> 
		BGCOLOR=white>
		<center>

	<? print "<table border='$show_border_for_debug'
			width='$header_width'
			$header_height
			cellpadding=0 cellspacing=0'>";

	print "<tr><td align=center valign=top height=1>\n";
	print_header_new($page_title, $subtitle, $url, $size, $image_bgcolor); 
	print "</td></tr>
			$end_of_header
			<!-- ------------------- end of header ------------- -->
			\n\n\n\n\n";
}






/************************************************************
*
*	prints all html 
*   & x's standard headers
*	
*   complementory to 'print_full_header'
*
************************************************************/
function print_full_footer($jobs=1, $help="") {
	global $independent_tables_mode;

	print "\n\n\n\n\n\n";
	?>
	<!-- ------------------- start of footer ------------- -->
	<BR>
	<? if($independent_tables_mode) {
		print "<TABLE border=0 cellpadding=0 cellspacing=0 width='100%'>";
	} else {
		print "</td></tr>";
	} ?>
	<tr><td valign=bottom>
		<? print_footer($jobs, $help) ?>
	</td></tr></table>
	</CENTER>
	</BODY></HTML>
	<!-- ------------------- end of footer ------------- --><?
}







function img_encode($str, $key="his secret key") {

	$str = mcrypt_cbc(MCRYPT_BLOWFISH_448, $key, $str, MCRYPT_ENCRYPT);
	$str = base64_encode($str);
	$str = urlencode($str);

	return $str;
}







	





/******************************************************************
*
*			show a progress indicator on the screen 
*                           (ie only)
*
*/
function print_progress_div($msg, $show_hide, $progress_image="") {
	//return; //debug
	
	if($show_hide == 'show') {

		?>
		<div id="progress" style="position:absolute; width:60%; height:20%; z-index:10; zOrder:10; zIndex:10; visibility: visible; background-color: #FFFFCC; layer-background-color: #FFFFCC; border: 1px none #000000; left: 20%; top: 30%">
		<table width="100%" border="4" cellspacing="7" cellpadding="9" height="100%">
		<tr><td align=center>
		<DIV ID=progressText name=progressText><? print $msg; ?></DIV>
		<? if($progress_image) { print "<IMG SRC='$progress_image' BORDER=0 TITLE='Please wait...'>"; } ?>
		</td></tr></table>
		</div>
		<?

	}
	else {
		?>
		<SCRIPT LANGUAGE="JavaScript">
		<!--
			document.all.progress.style.visibility = 'hidden';
		//-->
		</SCRIPT>
		<?
	}

	flush();
}




function update_progress_div($msg) {
	?>
	<SCRIPT LANGUAGE="JavaScript">
	<!--
	if(document.all.progressText)
		document.all.progressText.innerHTML = "<? print $msg; ?>";
	//-->
	</SCRIPT>
	<?
	flush();
}






/************************************************************

		return a list of users which fits into a sql:
		select x from y where user_id IN ($Users-List)

		you must provide the ()
	
************************************************************/
function get_users_for_sql_by_group($group=0, $name_or_id="id", $user_id_field="user_id", $users_table="users") {

	$sql = "SELECT username, $user_id_field FROM $users_table ";
	if ($group) { $sql .= " WHERE organization='$group' "; }

	$dbh = sql_query($sql, "user sql list retrieval error.");
	while ( $row = mysql_fetch_array($dbh) ) {
		if ($name_or_id == "id") { $field = $row[$user_id_field]; }
		else { $field = "'".$row['username']."'"; }

		$users[] = $field;
	}
	$ans = join("," , $users);
	return $ans;
}





function is_user_in_group($username, $CLIENT_GROUP) {
	$sql = "SELECT count(1) FROM users WHERE organization='$CLIENT_GROUP' AND username='$username'";
	$ans = get_single_scalar_from_query($sql);
	return $ans;
}





/**************************************************
	 
	 get source_id,
	 based on source

	default, 1 is for 'unknown'

**************************************************/
function get_source_id_for_source($source) {
	$sql = "SELECT source_id FROM sources WHERE source='$source'";
	$source_id = get_single_scalar_from_query($sql); 

	if (!$source_id) { $source_id = 1; }
	return $source_id;
}

// --- get source ----
function get_source_from_source_id($source_id) {
	
	if (!$source_id) { $source_id = 0; }

	$sql = "SELECT source FROM sources WHERE source_id=$source_id";
	$source_id = get_single_scalar_from_query($sql); 

	return $source_id;
}










/***************************************

    given a process id (of the OS)
	retun its status, time running, etc

   PROCESS FLAGS
       ALIGNWARN    001   print alignment warning msgs
       STARTING     002   being created
       EXITING      004   getting shut down
       PTRACED      010   set if ptrace (0) has been called
       TRACESYS     020   tracing system calls
       FORKNOEXEC   040   forked but didn't exec
       SUPERPRIV    100   used super-user privileges
       DUMPCORE     200   dumped core
       SIGNALED     400   killed by a signal


   PROCESS STATE CODES
       D   uninterruptible sleep (usually IO)
       R   runnable (on run queue)
       S   sleeping
       T   traced or stopped
       Z   a defunct ("zombie") process

****************************************/
function get_process_status($process_id) {
	
	/*
	$cmd = "ps aux ax -f -l --no-heading";
	$f = popen($cmd);
	$output = "";
	while( $s = fread($f, 65000) )
		$output .= $s;

	pclose($f);

	// ...
	//
	//

	switch($state_code) {
		case 'r': 
			$status='running'; 
			break;

		default:
			$status='unknown'; 
			break;
	}

	$ans['status'] = $status;
	$ans['time'] = $time;
	return $ans;
	*/
	return 1;
}




/*************************************************************************

	make an acronym for collocation.
	e.g.:
		"What the fuck is going here?" 
		returns
		W.T.F.I.G.H.

*************************************************************************/
function get_acronym($s, $delim='.', $upper=1) {
	$words = split("[- \_\.,\t]",$s);
	foreach($words as $word) {
		$first_letters[] = substr($word,0,1);
	}
	$ans = join("$delim",$first_letters) ."$delim";
	if ($upper) { $ans = strtoupper($ans); }
	return $ans;
}




/*************************************************************************

	read a file (or url)
	and strip html tags from it.
	
	$outfilename="": is not supoprted yet,
	and is meant for writing a file if 2 optional parameter is supplied.

*************************************************************************/
function strip_html_from_file($filename, $outfilename="") {
	$stripped_text = strip_tags( join('', file($filename) ) );
	return $stripped_text;
}
function print_stripped_file($filename) {
	$s = strip_html_from_file($filename);
	$s = preg_replace ("/\s*\n/","<P>\n",$s);
	print $s;
}




/*************************************************************************

	read a file (or url)
	and strip html tags from it.
	
	$outfilename="": is not supoprted yet,
	and is meant for writing a file if 2 optional parameter is supplied.

*************************************************************************/
function print_language_selection($this_language_id="", $multiple=0, $size=5) {

	if($multiple) {
		
		print "<SELECT MULTIPLE SIZE=$size NAME='language_ids[]' STYLE='width:150'>";
		$sql = "SELECT language_name, language_id FROM languages";
		$dbh = sql_query($sql);
		if (!$dbh) { print_error("language list retrieval error."); }

		while ( $row = mysql_fetch_row($dbh) ) {
			$tmp_language = $row[0];
			$tmp_language_id = $row[1];

			print "<OPTION ";
			if( $this_language_id ) { 
				if (in_array($tmp_language_id, $this_language_id) ) { print " SELECTED "; }
			}
			print " VALUE='$tmp_language_id'>$tmp_language ($tmp_language_id)</OPTION>\n";
		} 

		//$sys_id = get_language_id_from_language_name('system', "languages", 0, "language_id");
		//print "<OPTION VALUE='$sys_id'>System</OPTION>\n";
		print "</SELECT>";

	}
	else { // ------ single language selection

		print "<SELECT NAME='language_id'>";
		$sql = "SELECT language_name, language_id FROM languages";
		$dbh = sql_query($sql, "language retrieval error.");

		while ( $row = mysql_fetch_row($dbh) ) {
			$tmp_language = $row[0];
			$tmp_language_id = $row[1];

			print "<option ";
			if ($this_language_id == $tmp_language_id) { print " SELECTED "; }
			print " value='$tmp_language_id'>$tmp_language</option>\n";
		 } 
		print "<option ";
		if ($this_language_id == '%') { print " SELECTED "; }
		print "value='%'> all languages</option>\n";
		print "</select>";
	}
}





/*************************************************************************

	check if key $K is in array $ARR
	return tru or fals

*************************************************************************/
function has_key($arr, $key) {
	if(!is_array($arr)) { return false; } 
	$keys = array_keys($arr);
	return in_array($key,$keys); 
}





/*************************************************************************

	force browser to open "download" screen
	and download this page

	note: this function must run before any other output is printed ! 

*************************************************************************/
function force_download($filename, 
						$description='PHP3 Generated Data', 
						$content_type='application/x-something') {

	header( "Content-type: $content_type" );
	header( "Content-Disposition: attachment; filename=$filename" );
	header( "Content-Description: $description" );
}			



/*************************************************************************
		


*************************************************************************/
function get_content_type_for_filename($filename) {

	$ext = strtolower(ereg_replace (".*\.", "", $filename));
	
	switch($ext) {
		case "gif":
		case "jpg":
		case "jpeg":
		case "jpe":
		case "jfif":
		case "png":
		case "bmp":
		case "tif":
		case "wmf":
		case "art":
			$content_type='image/jpeg';
			break;

		case "txt":
		case "text":
			$content_type='text/plain';
			break;

		case "xml":
		case "doc-xml":
			$content_type='text/xml';
			break;

		case "avi":
		case "mpg":
		case "mpeg":
			$content_type='video/mpeg';
			break;

		case "swf":
			$content_type='application/flash';
			break;


		default:
			$content_type='text/html';
	}
}



?>