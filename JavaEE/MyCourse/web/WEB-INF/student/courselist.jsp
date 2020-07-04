<%@ page import="java.util.List" %>
<%@ page import="java.util.ArrayList" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%--
  User: Gao Tian
  Date: 2019/6/25
  Time: 21:23
--%>
<%@ page contentType="text/html;charset=UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>课程列表</title>
    <link rel="stylesheet" href="//cdn.bootcss.com/zui/1.9.1/css/zui.min.css">
    <script src="//cdn.bootcss.com/zui/1.8.1/lib/jquery/jquery.js"></script>
    <script src="//cdn.bootcss.com/zui/1.8.1/js/zui.min.js"></script>


    <style>
        .a-white-bottom:hover{
            text-decoration: none;
            border-bottom: 1px solid white;
        }

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

        #course-control{
            width: 97%;
            height: 50px;
            /*border: 1px solid black;*/
            margin: 0 auto;

        }
        #page{
            width: 90%;
            height: 100%;
            /* border: 1px solid red;*/
            margin: 0 auto;
        }
        .modal-dialog{
            width: 500px;
            height: 200px;
        }
        .modal-content h4{
            color: #3280fc;
            margin:0 10px;
            font-size: large;
            font-weight: bold;
        }
        .modal-content table{
            width: 80%;
            margin: 0 auto;
        }
        .modal-content label{
            font-size: large;
            font-weight: bold;
        }
        #enter-course-success{
            font-size: large;
        }

        .panel {
            width: 300px;
            height: 300px;
            margin-right: 20px;
            margin-left: 20px;
            margin-bottom: 40px;
            float: left;
            border: 1px solid #dadce0;
        }

/*        .panel:hover {
            border: 1px solid grey;
        }*/

        .panel-footer {
            height: 50px;
            background-color: white;
        }
        #panel-footer-code {

            font-size: medium;
            margin-top: 10px;
        }
        #panel-footer-btn {
            float: right;
            margin-top:-28px;
        }
        #panel-footer-btn a{
            margin-right: 5px;
        }

        .panel-heading {

            height: 80px;
            font-size: large;
            font-weight: bold;
            color: white;
        }
        .panel-heading strong{
            color: white;
            font-size: x-large;
        }
        .panel-heading p{
            color: white;
            font-size: small;
            float: right;
        }
        .panel-body {
            height: 150px;
            font-size: larger;
        }


    </style>
</head>


<body>

    <nav class="navbar navbar-inverse" role="navigation">
        <div class="container-fluid">

            <div class="navbar-header">
                <a class="navbar-brand navbar-font" href="/student/showCourseList.action"><strong class="nav-p">我的课堂</strong> </a>
            </div>

            <div class="collapse navbar-collapse  navbar-right">

                <ul class="nav navbar-nav">

                    <li class="dropdown">
                        <a href="your/nice/url" class="dropdown-toggle" data-toggle="dropdown"><p class="nav-p">${user.name} <b class="caret"></b></p></a>
                        <ul class="dropdown-menu" role="menu">
                            <li><a href="/logout.action">登出</a></li>
                        </ul>
                    </li>
                </ul>
            </div>
        </div>
    </nav>


    <div id="page">
        <div id="course-control">
            <button type="button" class="btn btn-primary" data-toggle="modal" data-target="#enter-course-modal">加入课程</button>
            <div class="modal fade" id="enter-course-modal">
                <div class="modal-dialog">
                    <div class="modal-content">
                        <div class="modal-header">
                            <h4 class="modal-title">加入课程</h4>
                        </div>
                        <div class="modal-body">
                            <table>
                                <tr>
                                    <td><label for="course-code">邀请码：</label></td>
                                    <td><input id="course-code" type="text" class="form-control input-lg"></td>
                                </tr>
                            </table>
                        </div>
                        <div class="modal-footer" id="enter-course-footer">
                            <button type="button" class="btn btn-default" data-dismiss="modal">关闭</button>
                            <button type="button" class="btn btn-primary" onclick="enterCourse()">加入</button>
                        </div>
                        <div class="modal-footer" id="create-success-footer" hidden="hidden">
                            <button type="button" class="btn btn-primary" onclick="enterSuccess()">完成</button>
                        </div>
                    </div>
                </div>
            </div>
        </div>

        <div id="cours-list">
            <%
                List<String> linears = new ArrayList<>();
                linears.add("background-image: linear-gradient(0deg,rgb(53,191,254) 0%,rgb(27,144,254) 100%)!important;");
                linears.add("background-image: linear-gradient(0deg,rgb(86,205,189) 0%,rgb(33,203,103) 100%)!important;");
                linears.add("background-image: linear-gradient(0deg,rgb(250,214,96) 0%,rgb(254,144,80) 100%)!important;");
                linears.add("background-image: linear-gradient(0deg,rgb(163,132,254) 0%,rgb(74,80,254) 100%)!important");
                linears.add("background-image: linear-gradient(0deg,rgb(254,127,172) 0%,rgb(249,93,85) 99%)!important;");
                linears.add("background-image: linear-gradient(0deg,rgb(69,213,211) 0%,rgb(4,173,184) 99%)!important;");
                request.setAttribute("linears", linears);
            %>

            <c:forEach items="${stuCourses}" var="course" varStatus="idx">
                <div class="panel panel-info">
                    <div class="panel-heading" style="${linears.get(idx.index % linears.size())}">
                        <a href="/student/notice.action?courseId=${course.id}" class="a-white-bottom"> <strong>  ${course.name}</strong><br> </a>
                        <p><i class="icon icon-user"></i>&nbsp;${course.studentCount}名学生</p>


                    </div>
                    <div class="panel-body">
                        <h2>近期作业</h2>
                        <c:forEach items="${course.stuTasks}" var="t">
                            <a  href="/student/taskDetail.action?courseId=${course.id}&taskId=${t.id}">${t.title}</a><br>
                        </c:forEach>
                    </div>
                    <div class="panel-footer">
                        <div id="panel-footer-code">
                            邀请码: ${course.code}&nbsp;&nbsp;教师：${course.teacher.name}
                        </div>
                        <div id="panel-footer-btn">
                            <button id="del-btn" class="btn btn-sm"  onclick="confirmDel('${course.id}', '${course.name}')">删除</button>
                        </div>
                    </div>
                </div>

            </c:forEach>
        </div>

    </div>


    <script>
        $(function () {
            $('#enter-course-modal').modal({
                backdrop : true,
                show : false
            })

        });

        function enterCourse() {
            var courseCode = $('#course-code');

            if (courseCode.val().trim() === '') {
                new $.zui.Messager("邀请码为空", {
                    type: 'info'
                }).show();
                return;
            }

            $.ajax({
                type: "POST",
                url: "/student/enterCourse",
                data: {courseCode : courseCode.val()},
                dataType: "json",

                success:function(data){
                    if (data.status === 0) {
                        $('.modal-body').html('<p id="enter-course-success"> 成功加入： ' + data.name + '</p>');
                        $('#enter-course-footer').hide();
                        $('#create-success-footer').show();

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

        function enterSuccess() {
            location.href = "/student/showCourseList.action";
        }

        function confirmDel(id, name) {
            bootbox.confirm(
                {
                    title: '是否退出？',
                    message: '课程： ' + name,
                    callback: function (result) {
                        if (result)
                            location.href = '/student/quitCourse.action?courseId=' + id;
                    }
                });
        }


    </script>



</body>
</html>
