<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%--
  User: Gao Tian
  Date: 2019/7/1
  Time: 21:17
--%>
<%@ page contentType="text/html;charset=UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>${teaCourse.name}</title>

    <link rel="stylesheet" href="//cdn.bootcss.com/zui/1.9.1/css/zui.min.css">
    <script src="//cdn.bootcss.com/zui/1.8.1/lib/jquery/jquery.js"></script>
    <script src="//cdn.bootcss.com/zui/1.8.1/js/zui.min.js"></script>
    <link href="/lib/bootbox/bootbox.min.css" rel="stylesheet">
    <script src="/lib/bootbox/bootbox.min.js"></script>

    <link rel="stylesheet" href="/lib/datatable/zui.datatable.min.css">
    <script src="/lib/datatable/zui.datatable.min.js"></script>

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
            width: 80%;
            height: 100%;
            /* border: 1px solid red;*/
            margin: 0 auto;
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
            <li><a href="/teacher/task.action?courseId=${teaCourse.id}"><p class="nav-p">作业</p></a></li>
            <li><a href="/teacher/resource.action?courseId=${teaCourse.id}"><p class="nav-p">资源</p></a></li>
            <li class="active"><a href="/teacher/student.action?courseId=${teaCourse.id}"><p class="nav-p">学生</p></a></li>
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
    <table class="table datatable">
    </table>


</div>

    <script>
        $(function () {

            $('.datatable').datatable(
                {
                    sortable: true,
                    data: {
                        cols: [
                            {width: 100, text: 'Email', type: 'string', flex: false, colClass: 'text-center'},
                            {width: 50, text: '姓名', type: 'string', flex: false,  colClass: 'text-center'},
                            {width: 70, text: '学号', type: 'string', flex: false, colClass: 'text-center'},
                            {width: 80, text: '学校', colClass: 'text-center'},
                            {width: 80, text: '院系', colClass: 'text-center'},
                            {width: 70, text: '专业', colClass: 'text-center'},
                            {width: 70, text: '班级', colClass: 'text-center'}
                        ],
                        rows: [
                            <c:forEach items="${students}" var="s">
                            {checked: false, data: ['${s.email}', '${s.name}', '${s.schoolId}', '${s.school}', '${s.dept}', '${s.major}', '${s.schoolClass}']},
                            </c:forEach>
                            // 更多数据
                        ]
                    }
                }
            );


        });

        function confirmDel(fileName, rId, courseId) {
            bootbox.confirm(
                {
                    title: '是否删除？',
                    message: '文件： ' + fileName,
                    callback: function (result) {
                        if (result) {
                            location.href="/teacher/deleteResource.action?resourceId=" + rId + "&courseId=" + courseId;
                        }
                    }
                });
        }
    </script>

</body>
</html>
