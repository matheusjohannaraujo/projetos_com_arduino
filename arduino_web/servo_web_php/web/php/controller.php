<?php 

require_once "config.php";

if(($servo = $_REQUEST['servo'] ?? false)){
    // $port = '/dev/ttyUSB0'; // LINUX e MAC    
    $port = "com4"; // WINDOWS
    if($servo == 'a' || $servo == 'b' || $servo == 'c' || $servo == 'd' || $servo == 'e'){
        if($linha["x"] != $servo){
            $pdo->query("UPDATE tb_servo SET angulo = '$servo' WHERE id = 1");
            streamSerial($servo, $port);
            exit;
        }
    }else{
        $servo = $linha["angulo"];
    }    
    if($servo == "a")
        $servo = "0°";
    else if($servo == "b")
        $servo = "45°";
    else if($servo == "c")
        $servo = "90°";
    else if($servo == "d")
        $servo = "135°";
    else if($servo == "e")
        $servo = "180°";
    exit($servo);
}else if(!empty($_REQUEST)){
    var_export($_REQUEST);
    exit("Erro durante processamento da requisição");
}