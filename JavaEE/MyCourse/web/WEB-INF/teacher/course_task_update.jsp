<%--
  User: Gao Tian
  Date: 2019/6/29
  Time: 13:05
--%>
<%@ page contentType="text/html;charset=UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>修改-${teaTask.title}</title>

    <link rel="stylesheet" href="//cdn.bootcss.com/zui/1.9.1/css/zui.min.css">
    <script src="//cdn.bootcss.com/zui/1.8.1/lib/jquery/jquery.js"></script>
    <script src="//cdn.bootcss.com/zui/1.8.1/js/zui.min.js"></script>
    <script src="/lib/wangEditor.min.js"></script>
    <link href="/lib/bootbox/bootbox.min.css" rel="stylesheet">
    <script src="/lib/bootbox/bootbox.min.js"></script>

    <style>
        .navbar-inverse{
            background-color: #3280fc;
            border: none;
        }
        .nav-p{
            color: white;
            height: 20px;
            margin-top: 10px;
        }
        .navbar-header {
            margin-top: 10px;
        }

        #page{
            width: 90%;
            height: 100%;
            /* border: 1px solid red;*/
            margin: 0 auto;
        }

        #task-title-text {
            height: 36px;
            line-height: 36px;
            border-bottom: 2px solid #3280fc;
            width: 100%;
            font-size: 18px;
            color: #2d2d2d;
            border-top: 0px;
            border-left: 0px;
            border-right: 0px;
            outline: none;
            float: right;
            margin-bottom: 20px;
            margin-top: 50px;
        }

        #update-task-btns .btn {
            float: right;
            margin-left: 10px;
        }
        #update-task-panel-footer {

            height: 50px;
            background-color: white;
        }
        
        #task-panel {
            width: 100%;
            height: 600px;
            margin: 0 auto;
            border: 0px white;
        }
        .w-e-text-container{
            height: 400px !important;
        }
        #deadline-div{
            width: 500px;
            height: 35px;
            float: left;
        }
        #deadline-choose{
            width: 100px;
            height: 30px;
            float: left;
        }
    </style>
</head>
<body>

    <nav class="navbar navbar-inverse" role="navigation">
        <div class="container-fluid">

            <div class="navbar-header">
                <a class="navbar-brand navbar-font" href="/teacher/showCourseList.action"><strong class="nav-p">我的课堂</strong> </a>
            </div>

            <ul class="nav navbar-nav">
                <li><a href="/teacher/notice.action?courseId=${teaCourse.id}"><p class="nav-p">公告</p></a></li>
                <li class="active"><a href="/teacher/task.action?courseId=${teaCourse.id}"><p class="nav-p">作业</p></a></li>
                <li><a href="/teacher/resource.action?courseId=${teaCourse.id}"><p class="nav-p">资源</p></a></li>
                <li><a href="/teacher/student.action?courseId=${teaCourse.id}"><p class="nav-p">学生</p></a></li>
            </ul>

            <div class="collapse navbar-collapse  navbar-right">

                <ul class="nav navbar-nav">

                    <li class="dropdown">
                        <a href="your/nice/url" class="dropdown-toggle" data-toggle="dropdown"><p class="nav-p">${user.name}老师 <b class="caret"></b></p></a>
                        <ul class="dropdown-menu" role="menu">
                            <li><a href="/logout.action">登出</a></li>
                        </ul>
                    </li>
                </ul>
            </div>
        </div>
    </nav>

    <div id="page">
        <div class="modal-content">
            <form action="/teacher/updateTask.action" method="POST" onsubmit="return checkForm();">
                <input type="text" id="content" name="taskContent" hidden="hidden">
                <input type="text" id="courseId" name="courseId" hidden="hidden" value="${teaCourse.id}">
                <input type="text" name="taskId" hidden="hidden" value="${teaTask.id}">
                <div class="panel" id="task-panel">
                    <div class="panel-body" id="update-task-panel-body">
                        <div id="task-title">
                            <input type="text" id="task-title-text" name="taskName" placeholder="作业名称" value="${teaTask.title}">
                        </div>
                        <div id="editor"></div>
                    </div>
                    <div class="panel-footer" id="update-task-panel-footer">
                        <div id="deadline-div">
                            <div class="checkbox-primary">
                                <input type="checkbox" id="deadline-checkbox" onclick="chooseDeadline()">
                                <label for="deadline-checkbox">截止日期</label></div>
                            <div id="deadline-choose"></div>
                            <input type="text" id="deadlineTime" name="deadlineTime" value="0" hidden="hidden">
                        </div>
                        <div id="update-task-btns">
                            <input class="btn btn-primary" type="submit" id="add-btn" value="提交">
                            <button class="btn" type="button" onclick="toTasks()">返回</button>
                        </div>
                    </div>
                </div>
            </form>
        </div>
    </div>

    <script>
        var E = window.wangEditor;
        var editor = new E('#editor');
        editor.create();

        $(function () {
            editor.txt.html('${teaTask.content}');
            var checkbox = $('#deadline-checkbox');
            var deadlineChoose = $('#deadline-choose');

            var taskDeadline = '${teaTask.hDeadline}';
            if (taskDeadline !== '') {
                checkbox.attr("checked", true);
                var arr = [];
                arr = taskDeadline.split(" ");
                console.log(arr);
                var d = arr[0] + "T" + arr[1];
                deadlineChoose.html('<input type="datetime-local" id="deadline" value="' + d + '"/>');
            }

        });

        function chooseDeadline() {
            var checkbox = $('#deadline-checkbox');
            var deadlineChoose = $('#deadline-choose');
            if (checkbox.is(':checked')) {
                var taskDeadline = '${teaTask.hDeadline}';
                if (taskDeadline !== '') {
                    var arr = [];
                    arr = taskDeadline.split(" ");
                    console.log(arr);
                    var d = arr[0] + "T" + arr[1];
                    deadlineChoose.html('<input type="datetime-local" id="deadline" value="' + d + '"/>');
                } else {
                    deadlineChoose.html('<input type="datetime-local" id="deadline"/>');
                }
            }
            else {
                deadlineChoose.html('');
            }
        }

        function checkForm() {
            var html = editor.txt.html();
            var title = $("#task-title-text");
            if (title.val().trim() === "") {
                title.attr("placeholder", "作业名称不能为空");
                return false;
            }
            var deadline = $('#deadline').val();

            if (deadline !== undefined && deadline !== null) {
                if (deadline === '') {
                    new $.zui.Messager("截止日期不能为空", {
                        type: 'info'
                    }).show();
                    return false;
                }
                if (new Date(deadline) < new Date()) {
                    new $.zui.Messager("截止日期不能小于当前时间", {
                        type: 'info'
                    }).show();
                    return false;
                }
                $('#deadlineTime').val(new Date(deadline).getTime());
            }

            $('#content').val(html);

            return true;
        }

        function toTasks() {
            location.href = "/teacher/task.action?courseId=${teaCourse.id}";
        }
    </script>

</body>
</html>
