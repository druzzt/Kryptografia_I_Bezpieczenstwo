<html>
<head> 
<title>DECIPHER ARC4</title>
<?php
	set_time_limit(0); // this makes php to not stop after few minutes
    $plain_text1 = '11110000 00101010 11101011 11000010 01000101 11010101 11111110 11000010 11010100 10011100 01000111 10100001 00010111 10100110 11011111 00100010 10110111 00001011 00100001 11000100 10111101 10000000 00001111 10100111 00011101 10000000 00010000 00001000 00011011 10011101 01011111 01010000 01001111 00010100 11110000 00001101 11110111 00110001 10110001 00110010 00110101 00110011 00011101 11011111 10110011 10100001 11000010 11001001 11001010 11100110 10010111 10100110 10101101 10100001 01111101 01011001 11010100 00100110 01101010 11111101 11111010 01011111 11000000 01000001 01000101 00110011';    
	$plain_text3 = ' '; // encrypted and to decrypt messages
	$token = strtok($plain_text1, " ");
	while ($token !== false)
    {
		$plain_text3=$plain_text3." ".chr(bindec(trim("$token")));
		$token = strtok(" ");
    }
	echo $plain_text3;
	$plain_text=$plain_text3;
	$key1 = '0';
    $key = 'cbce517f';	//append to the key2
	for($x=350000000; $x<=4294967297; $x++){ // this line can be splitted into multiple threads by dividing max number on separate servers4294967297..3000000000 and 3000000000..2000000000 and so on...
		$key2=dechex($x);
		$key2=$key2.$key;
		$td = mcrypt_module_open ('arcfour', '', 'stream', '');
		$key = substr ($key2, 0, mcrypt_enc_get_key_size ($td));
		$iv_size = mcrypt_enc_get_iv_size ($td);
		$iv = @mcrypt_create_iv ($iv_size);
		if (mcrypt_generic_init ($td, $key, $iv) != -1) {
			$c_t = mcrypt_generic ($td, $plain_text);
			mcrypt_generic_deinit ($td);
			mcrypt_generic_init ($td, $key, $iv);  
			$p_t = mdecrypt_generic ($td, $plain_text);
			mcrypt_generic_deinit ($td);
		}
		if(strlen($p_t) == strlen($plain_text)) {
			$j=mb_strlen($p_t);
			$longEnough=0;
				for($k=0;$k<$j;$k++){
					$schar=mb_substr($p_t,$k,1);
					if((ord($schar)>=32 && ord($schar)<=35) || (ord($schar)>=48 && ord($schar)<=59) || ord($schar)==64 || (ord($schar)>=65 && ord($schar)<=90) || (ord($schar)>=96 && ord($schar)<=122)){
						$longEnough++;
					}
				}
				if($longEnough==$j || $longEnough==$j-1 || $longEnough==$j-2 || $longEnough==$j-3 ){
					echo "<br>".$p_t."<br>"; // if decrypted message is long and valid enough to display
					$longEnough=0;
				}
			
		}
	}//a..z,A..Z,()!? "" ' '
    mcrypt_module_close ($td); // end of decryption module
?>
</head>
<body>
</FORM>
</body>
</html>
<!-- // MIGHT BE USEFUL FOR expanding this program
// bindec() and decbin();
  //dechex() and hexdec();	
	//$plain_text2HEX = bin2hex($plain_text2);
	//$isit = var_dump($plain_text === $plain_text2);
	//echo wordwrap($plain_text2,1,"<br>\n");
	//print_r ($plain_text2HEX=explode(" ",$plain_text2));
		//$myfile = fopen("encryptedFile.txt", "r") or die("Unable to open file!");	-->
		
