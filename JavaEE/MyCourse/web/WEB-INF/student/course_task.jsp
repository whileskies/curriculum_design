
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%--
  User: Gao Tian
  Date: 2019/6/27
  Time: 8:46
--%>
<%@ page contentType="text/html;charset=UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>${stuCourse.name}</title>

    <link rel="stylesheet" href="//cdn.bootcss.com/zui/1.9.1/css/zui.min.css">
    <script src="//cdn.bootcss.com/zui/1.8.1/lib/jquery/jquery.js"></script>
    <script src="//cdn.bootcss.com/zui/1.8.1/js/zui.min.js"></script>
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
            width: 80%;
            height: 100%;
            /* border: 1px solid red;*/
            margin: 0 auto;
        }


        #task-view{
            margin-top: 20px;
        }

        #task-title-panel {
            font-size: large;
            font-weight: bold;
            color: #007DDB;
        }

        #task-panel-footer{
            height: 40px;
        }
        #task-info-panel{
            float: left;
        }
    </style>
</head>
<body>

    <nav class="navbar navbar-inverse" role="navigation">
        <div class="container-fluid">

            <div class="navbar-header">
                <a class="navbar-brand navbar-font" href="/student/showCourseList.action"><strong class="nav-p">我的课堂</strong> </a>
            </div>

            <ul class="nav navbar-nav">
                <li ><a href="/student/notice.action?courseId=${stuCourse.id}"><p class="nav-p">公告</p></a></li>
                <li class="active"><a href="/student/task.action?courseId=${stuCourse.id}"><p class="nav-p">作业</p></a></li>
                <li><a href="/student/resource.action?courseId=${stuCourse.id}"><p class="nav-p">资源</p></a></li>
            </ul>

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

        <div id="course-info">
            <div class="panel panel-primary">
                <div class="panel-heading">
                    ${stuCourse.name}
                </div>
                <div class="panel-body">
                    邀请码：${stuCourse.code}
                </div>
            </div>
        </div>

        <c:if test="${empty stuTasks}">
            <h3>暂无作业</h3>
        </c:if>

        <div id="task-view">
            <c:forEach items="${stuTasks}" var="stuTask" varStatus="status">
                    <div class="panel panel-info">
                        <div class="panel-heading">
                            <a href="/student/taskDetail.action?courseId=${stuCourse.id}&taskId=${stuTask.id}">
                            <strong id="task-title-panel">${stuTask.title}</strong>
                            </a>
                        </div>
                        <div class="panel-body">
                           ${stuTask.plainTextContent}
                        </div>

                        <div class="panel-footer" id="task-panel-footer">

                            <p id="task-info-panel"><i class="icon icon-time"></i>&nbsp;更新时间:${stuTask.hUpdateTime}&nbsp;&nbsp;&nbsp;&nbsp;
                                <c:if test="${not empty stuTask.hDeadline}">
                                    <i class="icon icon-lock"></i>&nbsp;截止日期:${stuTask.hDeadline}&nbsp;&nbsp;&nbsp;&nbsp;
                                </c:if>
                                <i class="icon icon-user"></i>&nbsp;发布者:${stuTask.teacher.name}</p>
                        </div>
                    </div>
            </c:forEach>
        </div>

    </div>



</body>
</html>
