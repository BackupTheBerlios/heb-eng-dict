<?
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

?>
<html>
<head>
<meta content="text/html; charset=windows-1255" http-equiv="content-type">
<META NAME="Author" CONTENT="shula">
<title>dictionary input system?</title>
</head>

<body>
<h1 style="text-align: center;">hebrew to something dictionary</h1>
learn a new entry<br>
<form action="check_and_save_new_entry" method="get">
<table border="0">
<tbody>
<tr>
<td>Hebrew word</td>
<td><input name="hebrew"></td></tr>
<tr>
<td>plural<br></td>
<td><input name="hebrew_plural"></td></tr>
</table>


<table style="text-align: left; width: 50%;" border="0">
<tbody>
	<!-- ----------------------------------- -->
	<tr>
	
	<th>#</th>
	<th>to lang:</th>
	<th>translation</th>
	<th>Part of speech</th>
	<th>gender</th>

	</tr>

	
	<!-- ----------------------------------- -->
	<?
		for ($ent=0;$ent<6;$ent++) {
			# serial
			print "<tr><td>$ent</td>";
			
			# languages
			print "<td>" . show_select("lang[$ent]", $langs, 'en') . "</td>";
			
			# translation
			print "<td><input name=trans[$ent]></td>";

			#part of speech
			print "<td>" . show_select("part_of_speech[$ent]", $part_of_speeches, 'noun') . "</td>";

			#gender
			print "<td>" . show_select("gender[$ent]", $genders, 'male') . "</td>";
		}
	
		print "</tr>";

	?>

</tbody>
</table>

<input type=submit>

</form>
</body>
</html>


