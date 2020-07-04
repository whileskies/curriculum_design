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
    <link href="/lib/bootbox/bootbox.min.css" rel="stylesheet">
    <script src="/lib/bootbox/bootbox.min.js"></script>


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

        #stuCourse-control{
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
        #create-stuCourse-success{
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
        #del-btn{
            width: 50px;
            height: 30px;
        }


    </style>
</head>


<body>

    <nav class="navbar navbar-inverse" role="navigation">
        <div class="container-fluid">

            <div class="navbar-header">
                <a class="navbar-brand navbar-font" href="/teacher/showCourseList.action"><strong class="nav-p">我的课堂</strong> </a>
            </div>

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

        <div id="stuCourse-control">
            <button type="button" class="btn btn-primary" data-toggle="modal" data-target="#create-stuCourse-modal">创建课程</button>
            <div class="modal fade" id="create-stuCourse-modal">
                <div class="modal-dialog">
                    <div class="modal-content">
                        <div class="modal-header">
                            <h4 class="modal-title">创建课程</h4>
                        </div>
                        <div class="modal-body">
                            <table>
                                <tr>
                                    <td><label for="stuCourse-name">课程名：</label></td>
                                    <td><input id="stuCourse-name" type="text" class="form-control input-lg"></td>
                                </tr>
                            </table>
                        </div>
                        <div class="modal-footer" id="create-stuCourse-footer">
                            <button type="button" class="btn btn-default" data-dismiss="modal">关闭</button>
                            <button type="button" class="btn btn-primary" onclick="createCourse()">创建</button>
                        </div>
                        <div class="modal-footer" id="create-success-footer" hidden="hidden">
                            <button type="button" class="btn btn-primary" onclick="createSuccess()">完成</button>
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

            <c:forEach items="${teaCourses}" var="course" varStatus="idx">
                <div class="panel panel-info">
                    <div class="panel-heading" style="${linears.get(idx.index % linears.size())}">
                        <a href="/teacher/notice.action?courseId=${course.id}" class="a-white-bottom"> <strong>  ${course.name}</strong><br> </a>
                        <p><i class="icon icon-user"></i>&nbsp;${course.studentCount}名学生 </p>

                    </div>
                    <div class="panel-body">
                        <h2>近期作业</h2>
                        <c:forEach items="${course.teaTasks}" var="t">
                            <a href="/teacher/taskDetail.action?courseId=${course.id}&taskId=${t.id}">${t.title}</a><br>
                        </c:forEach>
                    </div>
                    <div class="panel-footer">
                        <div id="panel-footer-code">
                            邀请码: ${course.code}
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
            $('#create-stuCourse-modal').modal({
                backdrop : true,
                show : false
            })

        });

        function createCourse() {
            var courseName = $('#stuCourse-name');

            if (courseName.val().trim() === '') {
                new $.zui.Messager("课程名为空", {
                    type: 'info'
                }).show();
                return;
            }

            $.ajax({
                type: "POST",
                url: "/teacher/createCourse",
                data: {courseName : courseName.val()},
                dataType: "json",

                success:function(data){
                    if (data.status === 0) {
                        $('.modal-body').html('<p id="create-stuCourse-success"> 创建成功，邀请码为 ' + data.data.code + '</p>');
                        $('#create-stuCourse-footer').hide();
                        $('#create-success-footer').show();

                    } else {
                        new $.zui.Messager("创建失败", {
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

        function createSuccess() {
            location.href = "/teacher/showCourseList.action";
        }

        function confirmDel(id, name) {
            bootbox.confirm(
                {
                    title: '是否删除？',
                    message: '课程： ' + name + '<br>删除后所有内容将无法恢复（包括作业、资源）',
                    callback: function (result) {
                        if (result)
                            location.href = '/teacher/deleteCourse.action?courseId=' + id;
                    }
                });
        }


    </script>



</body>
</html>


