<?	
	$CONFIG_DIR = ".";
	require_once("$CONFIG_DIR/common-php-functions.inc");

function print_header($title="", $no_cache=0) {
	print "<HTML>\n<HEAD>\n";
	print "<TITLE>$title</TITLE>\n";
	print "<META NAME='Author' CONTENT='shula'>\n";

	$anti_cache = '<META http-equiv=expires content=0>
		<META http-equiv=pragma content=no-cache>
		<META http-equiv=cache-control content="no-cache, must-revalidate">';
	
	if($no_cache) { print $anti_cache; }
	print_charset_meta_tag('windows-1255');

	print "</HEAD><BODY>\n";
}
?>