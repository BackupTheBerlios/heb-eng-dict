<?
	$CONFIG_DIR = '.';
	require_once("$CONFIG_DIR/config.inc");
	require_once("$CONFIG_DIR/header.inc");
	require_once("$CONFIG_DIR/common-php-functions.inc");


	$genders[] = 'male';
	$genders[] = 'female';
	$genders[] = 'neuter';

	$part_of_speeches[] = 'noun';
	$part_of_speeches[] = 'verb';
	$part_of_speeches[] = 'adverb';
	$part_of_speeches[] = 'adjective';
	$part_of_speeches[] = 'pronoun';
	$part_of_speeches[] = 'preposition';

	$langs['ar'] = "Arabic";
	$langs['en'] = "English";
	$langs['fr'] = "French";
	$langs['es'] = "Espanol";
	$langs['de'] = "German";
	$langs['hi'] = "Hindi";
	$langs['ru'] = "Russian";
	

	function show_select($name, $array, $default='') {
		$s = "<select name='$name'>\n";
		foreach ($array as $key => $value) {
			$key==$default ? $sel = "selected"  :  $sel = "";
			$s .= "	<option value='$key' $sel>$value</option>\n";
		}
		$s .= "</select>\n";
		return $s;
	}


	print_header('dictionary input system');

?>

not implemented.

</form>
</body>
</html>


