<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%--
  User: Gao Tian
  Date: 2019/6/29
  Time: 13:05
--%>
<%@ page contentType="text/html;charset=UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>${teaTask.title}</title>

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

        #upload-file-div{
            width: 95%;
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
            <li class="active"><a href="/teacher/task.action?courseId=${teaCourse.id}"><p class="nav-p">作业</p></a></li>
            <li><a href="/teacher/resource.action?courseId=${teaCourse.id}"><p class="nav-p">资源</p></a></li>
            <li><a href="/teacher/student.action?courseId=${teaCourse.id}"><p class="nav-p">学生</p></a></li>

        </ul>

        <div class="collapse navbar-collapse  navbar-right">

            <ul class="nav navbar-nav">

                <li class="dropdown">
                    <a href="your/nice/url" class="dropdown-toggle" data-toggle="dropdown"><p class="nav-p">${user.name}老师
                        <b class="caret"></b></p></a>
                    <ul class="dropdown-menu" role="menu">
                        <li><a href="/logout.action">登出</a></li>
                    </ul>
                </li>
            </ul>
        </div>
    </div>
</nav>

<div id="page">
    <article class="article">
        <!-- 文章头部 -->
        <header>
            <h1>${teaTask.title}</h1>
            <!-- 文章属性列表 -->
            <dl class="dl-inline">
                <dt>发布者</dt>
                <dd>${teaTask.teacher.name}</dd>
                <dt>更新时间</dt>
                <dd>${teaTask.hUpdateTime}</dd>
                <dt>截止时间</dt>
                <dd>${teaTask.hDeadline}</dd>
            </dl>

        </header>
        <!-- 文章正文部分 -->
        <section class="content">
            ${teaTask.content}
        </section>
        <!-- 文章底部 -->
        <footer>
            <ul class="pager pager-justify">

            </ul>
        </footer>
    </article>

    <div id="task-files-div">
        <h3>学生作业：</h3>
        <p>
            总计：${allNum} &nbsp;&nbsp;&nbsp; 已交：${uploadNum} &nbsp;&nbsp;&nbsp; 未交：${allNum - uploadNum}
            &nbsp;&nbsp;&nbsp;&nbsp;
            <c:if test="${uploadNum > 0}">
                <a href="/file/taskZipFileDownload.action?taskId=${teaTask.id}">打包下载</a>
            </c:if>
        </p>

        <table class="table datatable">
            <thead>
            <tr>
                <th data-width="8%">姓名</th>
                <th data-width="11%">email</th>
                <th data-width="11%">学号</th>
                <th data-width="13%">专业</th>
                <th data-width="11%">班级</th>
                <th data-width="24%">作业</th>
                <th data-width="11%">提交时间</th>
                <th data-width="8%">操作</th>
            </tr>
            </thead>
            <tbody>
            <c:forEach items="${stuTaskFiles}" var="f">
                <tr>
                    <td>${f.user.name}</td>
                    <td>${f.user.email}</td>
                    <td>${f.user.schoolId}</td>
                    <td>${f.user.major}</td>
                    <td>${f.user.schoolClass}</td>
                    <td>${f.taskFile.fileName}</td>
                    <td>${f.taskFile.hUploadTime}</td>
                    <c:choose>
                        <c:when test="${not empty f.taskFile}">
                            <td>&nbsp;&nbsp;&nbsp;<a href="/file/teaTaskFileDownload.action?studentId=${f.user.id}&taskId=${teaTask.id}"><i class="icon icon-download-alt"></i></a> </td>
                        </c:when>
                        <c:otherwise>
                            <td></td>
                        </c:otherwise>
                    </c:choose>
                </tr>

            </c:forEach>
            </tbody>

        </table>



    </div>



    <script>
        $(function () {
            $('.datatable').datatable(
                {
                    sortable: true
                }
            );

        });


    </script>

</div>
</body>
</html>
