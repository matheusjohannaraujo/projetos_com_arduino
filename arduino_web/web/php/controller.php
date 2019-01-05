<?php 

ini_set("set_time_limit", 300);
ini_set("max_execution_time", 300);
ini_set("default_socket_timeout", 300);

require_once("DBCon.php");

$DBCon = new DBCon();
// $DBCon->setUser("vagrant");
// $DBCon->setPass("vagrant");
if (($pdo = $DBCon->getPdo())) {
	// $pdo->query("CREATE DATABASE IF NOT EXISTS db_arduino");
    $pdo->query("USE db_arduino");
    // $pdo->query("CREATE TABLE IF NOT EXISTS tb_arduino (id INT PRIMARY KEY AUTO_INCREMENT, chave CHAR(3) NOT NULL UNIQUE KEY, led VARCHAR(14) NOT NULL) ENGINE = MyISAM CHARSET=utf8 COLLATE utf8_unicode_ci");
    // $pdo->query("INSERT INTO tb_arduino VALUES (NULL, 'MJA', 'LED DESLIGADO!')");
}

function streamSerial($port = 'com2', $value = 'R', $result = false, $bits = 9600, $iterator = 1){
    exec("mode $port: BAUD=$bits PARITY=N data=8 stop=1 xon=off");
    if(($conexao = @fopen($port, "w+") ?? false)){
        fwrite($conexao, $value);
        if($result){
            $result = fgets($conexao);
        }
        fclose($conexao);
    }else{
        if($iterator <= 5){
            sleep(5);
            return streamSerial($port, $value, $result, $bits, $iterator++);
        }
        $result = "Erro ao estabelcer conexão!";                
    }
    return $result;
}

if(($led = $_REQUEST['led'] ?? false)){        
    $stmt = $pdo->query("SELECT led FROM tb_arduino WHERE id = 1");
    $linha = $stmt->fetch();
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
            $pdo->query("UPDATE tb_arduino SET led = '$valor' WHERE id = 1");
            exit(streamSerial($port, $led, true));
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