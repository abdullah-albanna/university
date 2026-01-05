<!DOCTYPE html>
<html>
  <head>
    <title>Assignment 3</title>
  </head>

  <body>
    <main>
      <form action="assignment_3_ext.php" method="post">
        <h2>Ablsotue Classes Registration</h2>
        <p style="color: red">
          * means required field <br/><br/>
          * You must agree our terms policy
        </p>

        <table>
          <tr>
            <td>
              <label for="student_name">Name: </label>
            </td>
            <td>
              <input type="text" id="student_name" name="student_name" required/>
              <span style="color: red"> * </span>
            </td>
          </tr>

          <tr>
            <td>
              <label for="student_email">E-mail: </label>
            </td>
            <td>
              <input type="email" id="student_email" name="student_email" required/>
              <span style="color: red"> * </span>
            </td>
          </tr>

          <tr>
            <td>
              <label for="time">Time: </label>
            </td>
            <td>
              <input type="text" id="time" name="time" />
            </td>
          </tr>

          <tr>
            <td>
              <label for="classes_name">Classes: </label>
            </td>
            <td>
              <textarea id="classes_name"  name="classes_name"></textarea>
            </td>
          </tr>
          <tr>
            <td>
              <label for="student_gender">Gender: </label>
            </td>
            <td>
              <input type="radio" name="student_gender" id="male_gender" value="male" required/><label for="male_gender">Male</label>
              <input type="radio" name="student_gender" id="female_gender" value="female" required/><label for="female_gender">Female</label>
              <span style="color: red"> * </span>
            </td>
          </tr>

          <tr>
            <td>
              <label for="select_menu">Select: </label>
            </td>
            <td>
              <select id="select_menu" name="select_menu" multiple>
                <option value="android">Android</option>
                <option value="java">Java</option>
                <option value="csharp">C#</option>
                <option value="database">Data Base</option>
              </select>
            </td>
          </tr>

          <tr>
            <td>
              <label for="agree">Agree</label>
            </td>
            <td>
              <input type="checkbox" id="agree" name="agree"/>
            </td>
          </tr>

          <tr>
            <td colspan="2">
              <input type="submit" id="submit" name="submit" value="Submit"/>
            </td>
          </tr>
        </table>
      </form>
    </main>
  </body>
</html>
