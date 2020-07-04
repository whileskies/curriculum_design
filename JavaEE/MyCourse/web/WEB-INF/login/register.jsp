
<%@ page contentType="text/html;charset=UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>我的课堂注册</title>

    <link rel="stylesheet" href="//cdn.bootcss.com/zui/1.8.1/css/zui.min.css">
    <script src="//cdn.bootcss.com/zui/1.8.1/lib/jquery/jquery.js"></script>
    <script src="//cdn.bootcss.com/zui/1.8.1/js/zui.min.js"></script>

    <style>
        .page {
            width: 100%;
            height: 100%;
            background: url("image/login_bg.jpg") fixed no-repeat center center;
            background-size: cover;
            position: absolute;
        }
        .navbar-inverse{
            background-color: #3280fc;
            border: none;
        }

        .navbar-header {
            /* margin-top: 5px;*/
        }
        .nav-p{
            color: white;
            height: 20px;
            margin-top: 5px;
        }
        #register-div {
            width: 600px;
            height: 700px;
            background-color: white;
            margin: 50px auto 0;
        }
        #register-title {
            width: 30%;
            margin: 0 auto;
            text-align: center;
            font-size: x-large;
            font-weight: bold;
            color: #3280fc;
            padding-top: 30px;
        }
        #select-role{
            text-align: center;
            margin-top: 20px;
        }
        .input-control{
            width: 80%;
            margin: 10px auto auto;
        }
        .form-control{
            height: 40px;
        }
        .input-control-label-left{
            margin-top: 4px;
            color: black;
            font-weight: bold;
        }
        .register-button {
            margin: 30px auto;
            width: 80%;
        }


    </style>
</head>
<body>

    <div class="page">

        <nav class="navbar navbar-inverse" role="navigation">
            <div class="container-fluid">
                <div class="navbar-header">
                    <a class="navbar-brand navbar-font"><strong class="nav-p">我的课堂</strong> </a>
                </div>
                <div class="collapse navbar-collapse">
                    <ul class="nav navbar-nav">

                    </ul>

                    <ul class="nav navbar-nav navbar-right">
                        <li></li>
                    </ul>
                </div>
            </div>
        </nav>


        <div id="register-div">
            <p id="register-title">注册</p>

            <div id="select-role">
                <div class="btn-group" data-toggle="buttons">
                    <label class="btn btn-primary active">
                        <input type="radio" name="role" value="s" checked onchange="changeRole()"> 学生注册
                    </label>
                    <label class="btn btn-primary">
                        <input type="radio" name="role" value="t" onchange="changeRole()"> 教师注册
                    </label>
                </div>
            </div>

            <div id="inputs">
                <div class="input-control has-label-left-lg has-icon-right">
                    <input id="email" type="email" class="form-control" placeholder="" >
                    <label for="email" class="input-control-label-left">邮箱:</label>
                </div>
                <div class="input-control has-label-left-lg has-label-right">
                    <input id="password" type="password" class="form-control" placeholder="">
                    <label for="password" class="input-control-label-left">密码:</label>
                </div>
                <div class="input-control has-label-left-lg has-label-right">
                    <input id="re-password" type="password" class="form-control" placeholder="">
                    <label for="re-password" class="input-control-label-left">确认密码:</label>
                </div>
                <div class="input-control has-label-left-lg has-icon-right">
                    <input id="name" type="text" class="form-control" placeholder="">
                    <label for="name" class="input-control-label-left">姓名:</label>
                </div>
                <div class="input-control has-label-left-lg has-icon-right">
                    <input id="schoolId" type="text" class="form-control" placeholder="">
                    <label for="schoolId" class="input-control-label-left" id="change-school-id">学号:</label>
                </div>
                <div class="input-control has-label-left-lg has-icon-right">
                    <input id="school" type="text" class="form-control" placeholder="">
                    <label for="school" class="input-control-label-left">学校:</label>
                </div>
                <div class="input-control has-label-left-lg has-icon-right">
                    <input id="dept" type="text" class="form-control" placeholder="">
                    <label for="dept" class="input-control-label-left">学院:</label>
                </div>
                <div class="input-control has-label-left-lg has-icon-right teacher-none">
                    <input id="major" type="text" class="form-control" placeholder="">
                    <label for="major" class="input-control-label-left">专业:</label>
                </div>
                <div class="input-control has-label-left-lg has-icon-right teacher-none">
                    <input id="class" type="text" class="form-control" placeholder="">
                    <label for="class" class="input-control-label-left">班级:</label>
                </div>

                <button class="btn btn-block btn-primary register-button" type="button" onclick="submit()">注册</button>
            </div>

        </div>

    </div>

    <script>
        function submit() {
            var ok = true;
            var email = $('#email');
            if (email.val().trim() === '') {
                email.val("");
                email.attr('placeholder', '邮箱不能为空');
                ok = false;
            }
            else if (!checkEmail(email.val().trim())) {
                email.val("");
                email.attr('placeholder', '邮箱格式不正确');
                ok = false;
            }

            var password = $('#password');
            if (password.val().trim() === '') {
                password.val("");
                password.attr('placeholder', '密码不能为空');
                ok = false;
            }
            else if (!checkPass(password.val().trim())) {
                password.val("");
                password.attr('placeholder', '密码应由6-18位的字母、数字、下划线组成');
                ok = false;
            }

            var repassword = $('#re-password');
            if (repassword.val().trim() === '') {
                repassword.val("");
                repassword.attr('placeholder', '请重复密码');
                ok = false;
            }
            else if (repassword.val() !== password.val()) {
                repassword.val("");
                repassword.attr('placeholder', '两次密码不一致');
                ok = false;
            }

            var name = $('#name');
            if (name.val().trim() === '') {
                name.val("");
                name.attr('placeholder', '姓名不能为空');
                ok = false;
            }

            if (!ok) return;

            var data = {};
            var schoolId = $('#schoolId');
            var school = $('#school');
            var dept = $('#dept');
            if (role === 's') {
                var major = $('#major');
                var schoolClass = $('#class');

                data = {role : 's', email: email.val().trim(), password: password.val().trim(), name: name.val().trim(),
                    schoolId: schoolId.val().trim(), school: school.val().trim(), dept: dept.val().trim(), major: major.val().trim(),
                    schoolClass: schoolClass.val().trim()};
            } else if (role === 't') {
                data = {role : 't', email: email.val().trim(), password: password.val().trim(), name: name.val().trim(),
                    schoolId: schoolId.val().trim(), school: school.val().trim(), dept: dept.val().trim()};
            }

            $.ajax({
                type: "POST",
                url: "/register",
                data: data,
                dataType: "json",

                success:function(data){
                    if (data.status === 0) {
                        new $.zui.Messager(data.msg + ', 正在跳转', {
                            type: 'success'
                        }).show();
                        if (data.data.user_role === 't')
                            setTimeout('location.href = "/teacher/showCourseList.action"', 2000);
                        else if (data.data.user_role === 's')
                            setTimeout('location.href = "/student/showCourseList.action"', 2000);
                    } else {
                        new $.zui.Messager(data.msg , {
                            type: 'danger'
                        }).show();
                    }
                },

                error: function () {
                    new $.zui.Messager('网络似乎出问题了...', {
                        type: 'danger'
                    }).show();
                }

            });

        }

        function checkEmail(str) {
            var re = /^[A-Za-z\d]+([-_.][A-Za-z\d]+)*@([A-Za-z\d]+[-.])+[A-Za-z\d]{2,4}$/;
            return re.test(str);
        }

        //由6-18位的字母、数字、下划线组成
        function checkPass(str) {
            var re = /^[0-9a-zA-Z_]{6,18}$/;
            return re.test(str);
        }

        var role = 's';

        function changeRole() {
            role = $('[name=role]:checked').val();
            var teacherNone = $('.teacher-none');
            if (role === 's') {
                teacherNone.each(function (i, e) {
                    $(e).show();
                });
                $('#change-school-id').html("学号:");

            }
            else if (role === 't') {
                teacherNone.each(function (i, e) {
                    $(e).hide();
                });
                $('#change-school-id').html("教工号:");
            }
        }


    </script>
</body>
</html>
