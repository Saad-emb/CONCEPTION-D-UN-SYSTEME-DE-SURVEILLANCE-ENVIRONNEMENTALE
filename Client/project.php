<?php

$angle = "";
if(isset($_POST['angle'])) {
    $angle = $_POST['angle'];
    $output = shell_exec("./write_servo $angle");
    echo "Angle set to: $angle";
}
$temp = "";
$hum = "";
if(file_exists("c-bin/data.txt")) {
    $data = file_get_contents("c-bin/data.txt");
    $values = explode(" ", $data);
    if(count($values) == 2) {
        $temp = $values[0];
        $hum = $values[1];
    }
}
$latitude = "";
$longitude = "";
if(file_exists("c-bin/data_gps.txt")) {
    $data = file_get_contents("c-bin/data_gps.txt");
    $values = explode(",", $data);
    if(count($values) == 2) {
        $latitude = trim(str_replace("Latitude:", "", $values[0]));
        $longitude = trim(str_replace("Longitude:", "", $values[1]));
    }
}
$temp_status = "";
$output = shell_exec("cat /sys/class/gpio/gpio22/value");
if(trim($output) == "1") {
    $temp_status = '<span style="color:green;">Temp is good</span>';
}
if(trim($output) == "0") {
    $temp_status = '<span style="color:red;">Temp is bad</span>';
}
$db = new PDO('sqlite:/home/saad/data_db.db');

$results = $db->query('SELECT * FROM data ORDER BY timestamp DESC'); 
$data = $results->fetchAll();
?>
<html>
<head>
    <title>Servo Control and DHT11 Readings</title>
<meta http-equiv="Refresh" content="30">
    <style>
        body {
            font-family: Arial, sans-serif;
            background-color: #f7f7f7;
            text-align: center;
        }
        table {
        border-collapse: collapse;
        width: 50%;
        margin: auto;
        font-family: Arial, sans-serif;
        font-size: 14px;
    }

    th, td {
        border: 1px solid #ddd;
        padding: 8px;
        text-align: center;
    }

    th {
        background-color: #f2f2f2;
    }

    tr:nth-child(even) {
        background-color: #f2f2f2;
    }
        h1 {
            color: #337ab7;
        }
        form {
            margin-top: 20px;
            padding: 10px;
            background-color: #fff;
            border-radius: 5px;
            box-shadow: 0 0 5px rgba(0,0,0,.2);
        }
        input[type="text"] {
            width: 80px;
            margin: 5px;
            padding: 5px;
            border-radius: 3px;
            border: 1px solid #ccc;
        }
        input[type="submit"] {
            margin: 5px;
            padding: 5px 10px;
            background-color: #337ab7;
            color: #fff;
            border-radius: 3px;
            border: none;
            cursor: pointer;
        }
        .reading {
            display: inline-block;
            margin-right: 10px;
            padding: 5px;
            background-color: #fff;
            border-radius: 3px;
            border: 1px solid #ccc;
        }
    </style>
</head>
<body>
<h1>Smart Package Monitoring</h1>
<form method="post">
    <label for="angle">Door angle (0-90):</label>
    <input type="text" name="angle" id="angle" value="<?php echo htmlspecialchars($angle); ?>">
    <input type="submit" value="Submit">
</form>
<?php if($temp_status != ""): ?>
    <div>
        <span class="reading"><?php echo $temp_status; ?></span>
    </div>
    <?php endif; ?>
<?php if($temp != "" && $hum != ""): ?>
<div>
    <span class="reading">Temperature: <?php echo $temp; ?> &deg;C</span>
    <span class="reading">Humidity: <?php echo $hum; ?>%</span>
</div>
<div>
    <span class="reading">Latitude: <?php echo $latitude; ?></span>
    <span class="reading">Longitude: <?php echo $longitude; ?></span>
</div>
<?php endif; ?>
<?php
// Check if latitude and longitude variables are set
if(!empty($latitude) && !empty($longitude)) {
  // Generate Google Maps link
  $google_maps_link = "https://www.google.com/maps?q={$latitude},{$longitude}";
  // Output link
  echo "<a href='{$google_maps_link}' target='_blank'>View live location</a>";
}

?>
<h3 >Package monitoring history</h3>
<table>
    <tr>
        <th>Temperature</th>
        <th>Humidity</th>
        <th>Latitude</th>
        <th>Longitude</th>
        <th>Timestamp</th>
    </tr>
    <?php foreach ($data as $row): ?>
    <tr>
        <td><?php echo $row['temperature']; ?></td>
        <td><?php echo $row['humidity']; ?></td>
        <td><?php echo $row['latitude']; ?></td>
        <td><?php echo $row['longitude']; ?></td>
        <td><?php echo date('Y-m-d H:i:s', $row['timestamp']); ?></td>
    </tr>
    <?php endforeach; ?>

</body>
</html>
