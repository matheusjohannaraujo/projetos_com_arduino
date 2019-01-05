<?php 

require_once "config.php";

if(($led = $_REQUEST['led'] ?? false)){
    // $port = '/dev/ttyUSB0'; // LINUX e MAC    
    $port = "com4"; // WINDOWS
    if($led == 'L' || $led == 'D'){
        $valor = $led;
        if($led == 'L'){
            $valor = "LED LIGADO!";
        }else{
            $valor = "LED DESLIGADO!";
        }
        if($linha["led"] != $valor){
            $pdo->query("UPDATE tb_led SET led = '$valor' WHERE id = 1");
            exit(streamSerial($led, $port, true));
        }else{
            exit($linha["led"]);
        }
    }else if($led == 'R'){
        exit($linha["led"]);
    }
}else if(!empty($_REQUEST)){
    var_export($_REQUEST);
    exit("Erro durante processamento da requisição");
}