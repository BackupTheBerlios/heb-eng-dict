<?	
	$CONFIG_DIR = '.';
	require_once("$CONFIG_DIR/config.inc");
	require_once("$CONFIG_DIR/common-php-functions.inc"); 
	require_once("$CONFIG_DIR/dict_library.inc"); 
	require_once("$CONFIG_DIR/header.inc");
	
	print_header();
	connect_to_mysql();

	print "server time: " . time() . " <BR>\n"; 
	print "plural: " . $HTTP_GET_VARS['entry_plural'] . " <BR>\n";
	print "trans[]: " . $HTTP_GET_VARS['trans'][0] . " <BR>\n";
	print "part_of_speech[]: " . $HTTP_GET_VARS['part_of_speech'][0] . " <BR>\n";
	print "lang[]: " . $HTTP_GET_VARS['lang'][0] . " <BR>\n";	
	print "gender[]: " . $HTTP_GET_VARS['gender'][0] . " <BR>\n";
	print "<HR>";

	// security: validate accuracy of params, add slashes
	$entry = $HTTP_GET_VARS['entry'];
	$entry_plural = $HTTP_GET_VARS['entry_plural'];
	$sql = "INSERT INTO entries SET 
			entry='$entry'
			";
			//part_of_speech='$part_of_speech',
			//gender='$gender'

	debug($sql); //$entry_id=7;
	$entry_id = sql_insert($sql);

	$num_translations = count($HTTP_GET_VARS['trans']);

	foreach($HTTP_GET_VARS['trans'] as $i=>$trans) {

		if( ! $trans) { continue; }
		
		$part_of_speech = $HTTP_GET_VARS['part_of_speech'][$i];
		$lang = $HTTP_GET_VARS['lang'][$i];
		$gender = $HTTP_GET_VARS['gender'][$i];

		if( ! in_array($gender, $allowed_genders)) { $gender=""; }
		if( ! in_array($part_of_speech, $allowed_parts_of_speech)) { $part_of_speech=""; }

		$sql = "INSERT INTO translations SET 
				entry_id='$entry_id',
				trans='$trans', 
				lang_id='$lang'
				";
		debug($sql);
		$trans_id = sql_insert($sql);
	}

?>


<hr>
<form>
<input type=button value="Finish" onClick="location.href = 'http://www.1112.net/lastpage.html'">
&nbsp;&nbsp;&nbsp;&nbsp;
<input type=button value="Add Another Entry" onClick="history.back()">
&nbsp;&nbsp;&nbsp;&nbsp;
<input type=button value="Show database" onClick="location.href = 'show_all.php'">
</form>
</BODY>
</HTML>
