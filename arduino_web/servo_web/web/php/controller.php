<?php 

ini_set("set_time_limit", 300);
ini_set("max_execution_time", 300);
ini_set("default_socket_timeout", 300);

require_once("DBCon.php");

$DBCon = new DBCon();
$DBCon->setUser("vagrant");
$DBCon->setPass("vagrant");
if (($pdo = $DBCon->getPdo())) {
	// $pdo->query("CREATE DATABASE IF NOT EXISTS db_arduino");
    $pdo->query("USE db_arduino");
    // $pdo->query("CREATE TABLE IF NOT EXISTS tb_servo (id INT PRIMARY KEY AUTO_INCREMENT, chave CHAR(3) NOT NULL UNIQUE KEY, angulo CHAR(1) NOT NULL) ENGINE = MyISAM CHARSET=utf8 COLLATE utf8_unicode_ci");
    // $pdo->query("INSERT INTO tb_servo VALUES (NULL, '012', 'a')");
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

if(($x = $_REQUEST['x'] ?? false)){
    $stmt = $pdo->query("SELECT angulo FROM tb_servo WHERE id = 1");
    $linha = $stmt->fetch();
    // $port = '/dev/ttyUSB0'; // LINUX e MAC    
    $port = "com4"; // WINDOWS
    if($x == 'a' || $x == 'b' || $x == 'c' || $x == 'd' || $x == 'e'){
        if($linha["x"] != $x){
            $pdo->query("UPDATE tb_servo SET angulo = '$x' WHERE id = 1");
            streamSerial($port, $x);
            exit;
        }
    }else{
        $x = $linha["angulo"];
    }    
    if($x == "a")
        $x = "0°";
    else if($x == "b")
        $x = "45°";
    else if($x == "c")
        $x = "90°";
    else if($x == "d")
        $x = "135°";
    else if($x == "e")
        $x = "180°";
    exit($x);
}else if(!empty($_REQUEST)){
    var_export($_REQUEST);
    exit("Erro durante processamento da requisição");
}