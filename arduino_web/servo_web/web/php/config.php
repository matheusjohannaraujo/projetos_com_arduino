<?php

ini_set("set_time_limit", 300);
ini_set("max_execution_time", 300);
ini_set("default_socket_timeout", 300);

require_once "DBCon.php";
require_once "streamSerial.php";

if(!($_REQUEST['servo'] ?? false)){
    exit;
}

$DBCon = new DBCon();
$DBCon->setUser("vagrant");
$DBCon->setPass("vagrant");
if (($pdo = $DBCon->getPdo())) {
	$pdo->query("CREATE DATABASE IF NOT EXISTS db_arduino");
    $pdo->query("USE db_arduino");
    $pdo->query("CREATE TABLE IF NOT EXISTS tb_servo (id INT PRIMARY KEY AUTO_INCREMENT, chave CHAR(3) NOT NULL UNIQUE KEY, angulo CHAR(1) NOT NULL) ENGINE = MyISAM CHARSET=utf8 COLLATE utf8_unicode_ci");
}

$stmt = $pdo->query("SELECT angulo FROM tb_servo WHERE id = 1");
$linha = $stmt->fetch();
if(!$linha){
    $pdo->query("INSERT INTO tb_servo VALUES (NULL, '012', 'a')");
}