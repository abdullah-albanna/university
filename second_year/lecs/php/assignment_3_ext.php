<?php if (isset($_POST["submit"])) {?>
<div>
  <table >
    <tr>
      <td>Name</td>
      <td><?php echo $_POST["student_name"]?></td>
    </tr>

    <tr>
      <td>Email</td>
      <td><?php echo $_POST["student_email"]?></td>
    </tr>

    <tr>
      <td>Time</td>
      <td><?php echo $_POST["time"]?></td>
    </tr>

    <tr>
      <td>Classes</td>
      <td><?php echo $_POST["classes_name"]?></td>
    </tr>

    <tr>
      <td>Gender</td>
      <td><?php echo $_POST["student_gender"]?></td>
    </tr>

    <tr>
      <td>Selection</td>
      <td>
        <?php
        foreach ($_POST["select_menu"] as $item) {
            echo $item;
        }
    ?>
      </td>
    </tr>
    
  </table>
</div>
<?php } ?>
