<!DOCTYPE html>
<html>
  <head>
    <title>Assignment 4</title>
  </head>

  <body>
    <main>
      <form action="assignment_4.php" method="get">
        <table border="1" style="width: 500px;">
          <tr>
            <td colspan="2">
              <h2 style="margin: auto;">Age Calculator</h2>
            </td>
          </tr>
          <tr>
            <td>
              <label for="current_date">Current Year: </label>
            </td>
            <td>
              <input type="text" id="current_date" name="current_date"/>
            </td>
          </tr>

          <tr>
            <td>
              <label for="DoB">Your DoB: </label>
            </td>
            <td>
              <input type="text" id="DoB" name="DoB" required/>
            </td>
          </tr>

          <tr>
            <td colspan="2">
              <input type="submit" id="submit" name="calc" value="calculate"/>
            </td>
          </tr>

          <tr>
            <td>
              <label for="user_age">Your age is: </label>
            </td>
            <td>
              <p style="size: 24pt; color: cyan;">
                <?php
                if (isset($_GET["calc"])) {
                    $currentDate;

                    if ($_GET["current_date"] != "") {
                        $currentDate = $_GET["current_date"];
                    } else {
                        $date = new DateTime();
                        $currentDate = $date->format("o");
                        var_dump($currentDate);
                    }

                    $DoB = $_GET["DoB"];


                    printf("%d years", $currentDate - $DoB);
                }
                ?>
              </p>
            </td>
          </tr>
        </table>
      </form>
    </main>
  </body>
</html>
