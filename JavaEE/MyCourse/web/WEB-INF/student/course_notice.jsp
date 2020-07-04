<%@ taglib prefix="s" uri="/struts-tags" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ taglib prefix="fn" uri="http://java.sun.com/jsp/jstl/functions" %>
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
            width: 80%;
            height: 100%;
            /* border: 1px solid red;*/
            margin: 0 auto;
        }

        #teaNotice-title-text {
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
            margin-bottom: 10px;
        }
        .w-e-text-container{
            height: 200px !important;
        }
        #add-teaNotice-btns .btn {
            float: right;
            margin-left: 10px;
        }
        #add-teaNotice-panel-footer {
            height: 50px;
            /*background-color: white;*/
        }
        #teaNotice-view{
            margin-top: 20px;
        }
        #add-teaNotice-btn {
            height: 40px;
        }
        #teaNotice-title-panel {
            font-size: large;
            font-weight: bold;
            color: #007DDB;
        }
        #del-btn {
            width: 48px;
            height: 25px;
            text-align:center;
            float: right;
        }
        #teaNotice-panel-footer{
            height: 40px;
        }
        #teaNotice-info-panel{
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
                <li class="active"><a href="/student/notice.action?courseId=${stuCourse.id}"><p class="nav-p">公告</p></a></li>
                <li><a href="/student/task.action?courseId=${stuCourse.id}"><p class="nav-p">作业</p></a></li>
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


        <c:if test="${empty stuNotices}">
            <h3>暂无公告</h3>
        </c:if>

        <div id="teaNotice-view">
            <c:forEach items="${stuNotices}" var="stuNotice" varStatus="status">
                    <div class="panel">
                        <div class="panel-heading">
                            <a data-toggle="modal" data-target="#myLgModal${status.index}" onclick="closeAddNotice()">
                            <strong id="teaNotice-title-panel">${stuNotice.title}</strong>
                            </a>
                        </div>
                        <div class="panel-body">
                           ${stuNotice.plainTextContent}
                        </div>

                        <div class="panel-footer" id="teaNotice-panel-footer">
                            <p id="teaNotice-info-panel"><i class="icon icon-time"></i>&nbsp;发布时间：${stuNotice.hUpdateTime}&nbsp;&nbsp;<i class="icon icon-user"></i>&nbsp;发布者：${stuNotice.teacher.name}</p>
                        </div>
                    </div>

                <div class="modal fade" id="myLgModal${status.index}">
                    <div class="modal-dialog modal-lg">
                        <div class="modal-content">
                            <div class="modal-header">
                                <button type="button" class="close" data-dismiss="modal"><span aria-hidden="true">×</span><span class="sr-only">关闭</span></button>
                                <h4 class="modal-title">公告</h4>
                            </div>
                                    <article class="article">
                                        <!-- 文章头部 -->
                                        <header>
                                            <h1>${stuNotice.title}</h1>
                                            <!-- 文章属性列表 -->
                                            <dl class="dl-inline">
                                                <dt>发布者</dt>
                                                <dd>${stuNotice.teacher.name}</dd>
                                                <dt>发布时间</dt>
                                                <dd>${stuNotice.hUpdateTime}</dd>
                                            </dl>

                                        </header>
                                        <!-- 文章正文部分 -->
                                        <section class="content">
                                                ${stuNotice.content}
                                        </section>
                                        <!-- 文章底部 -->
                                        <footer>
                                            <ul class="pager pager-justify">

                                            </ul>
                                        </footer>
                                    </article>
                        </div>
                    </div>
                </div>
            </c:forEach>
        </div>


</body>
</html>
