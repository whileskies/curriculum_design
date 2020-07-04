<%@ page contentType="text/html;charset=UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>登录</title>

    <link rel="stylesheet" href="//cdn.bootcss.com/zui/1.8.1/css/zui.min.css">
    <script src="//cdn.bootcss.com/zui/1.8.1/lib/jquery/jquery.js"></script>
    <script src="//cdn.bootcss.com/zui/1.8.1/js/zui.min.js"></script>

    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />

    <style>
        .page {
            width: 100%;
            height: 100%;
            background: url("/image/login_bg.jpg") fixed no-repeat center center;
            background-size: cover;
            position: absolute;
        }





        .login {
            width: 500px;
            height: 500px;
            background-color: #ffffff;
            margin-top: 100px;
        }

        p, .input-control {
            margin-top: 30px;
        }

        .login p {
            text-align: center;
            font-size: 25px;
            font-weight: bold;
            color: #3280fc;
            margin-bottom: 50px;
            margin-top: 50px;
        }

        .input-control, #check_table, #submit-div {
            width: 70%;
            height: 60px;
            margin: 0 auto;
        }

        .input-control-label-left {
            margin-top: 5px;
        }

        .input-control-check {
            width: 100%;
        }

        #image {
            height: 40px;
            width: 120px;
            margin-bottom: 13px;
            margin-left: 10px;
        }

        #submit-div {
            text-align: center;
        }

        #submit {
            width: 330px;
            margin-top: 30px;
        }

        #register-p {
            color: black;
            font-size: 15px;
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


    <div class="login container">
        <p>我的课堂</p>
        <div class="input-control has-label-left has-icon-right">
            <input id="inputEmail" type="email" class="form-control input-lg" placeholder="">
            <label for="inputEmail" class="input-control-label-left">邮箱:</label>
        </div>

        <div class="input-control has-label-left has-label-right">
            <input id="inputPassword" type="password" class="form-control input-lg" placeholder="">
            <label for="inputPassword" class="input-control-label-left">密码:</label>
        </div>

        <table id="check_table">
            <tr>
                <td>
                    <div class="input-control has-label-left has-label-right input-control-check">
                        <input id="verificationCode" type="text" class="form-control input-lg" placeholder="">
                        <label for="verificationCode" class="input-control-label-left">验证码:</label>
                    </div>
                </td>
                <td>
                    <img src="/verificationCode" alt="验证码" id="image" onclick="reload()">
                </td>
            </tr>
        </table>

        <div id="submit-div">
            <input class="btn btn-primary" type="submit" value="登陆" id="submit" onclick="submit()">
        </div>

        <p id="register-p">没有帐号？<a href="/toRegister">注册</a></p>

    </div>
</div>


<script>
    $(function () {
        $(document).keyup(function (e) {
            if (e.keyCode === 13) {
                submit();
            }
        });

    });

    function reload() {
        $('#image').attr("src", "/verificationCode?date=" + new Date());
        $('#verificationCode').val("");
    }

    function submit() {
        var email = $('#inputEmail');
        var pass = $('#inputPassword');
        var verificationCode = $('#verificationCode');

        if (email.val() === '') {
            new $.zui.Messager('email为空', {
                type: 'danger'
            }).show();
            return;
        }
        if (pass.val() === '') {
            new $.zui.Messager('密码为空', {
                type: 'danger'
            }).show();
            return;
        }
        if (verificationCode.val() === '') {
            new $.zui.Messager('验证码为空', {
                type: 'danger'
            }).show();

            return;
        }

        $.ajax({
            type: "POST",
            url: "/login",
            data: {email: email.val(), password: pass.val(), verificationCode: verificationCode.val()},
            dataType: "json",

            success: function (data) {
                if (data.status === 0) {
                    if (data.data.user_role === 't') {
                        location.href = "/teacher/showCourseList.action";
                    } else if (data.data.user_role === 's') {
                        location.href = "/student/showCourseList.action";
                    }
                } else {

                    new $.zui.Messager(data.msg, {
                        type: 'danger'
                    }).show();

                    reload();
                }
            },

            error: function () {
                new $.zui.Messager('请求失败', {
                    type: 'danger'
                }).show();
            }

        });
    }


</script>

</body>

</html>