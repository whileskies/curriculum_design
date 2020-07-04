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
    <title>${stuTask.title}</title>

    <link rel="stylesheet" href="//cdn.bootcss.com/zui/1.9.1/css/zui.min.css">
    <script src="//cdn.bootcss.com/zui/1.8.1/lib/jquery/jquery.js"></script>
    <script src="//cdn.bootcss.com/zui/1.8.1/js/zui.min.js"></script>
    <link href="/lib/bootbox/bootbox.min.css" rel="stylesheet">
    <script src="/lib/bootbox/bootbox.min.js"></script>
    <link href="/lib/uploader/zui.uploader.min.css" rel="stylesheet">
    <script src="/lib/uploader/zui.uploader.min.js"></script>

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
        <article class="article">
            <!-- 文章头部 -->
            <header>
                <h1>${stuTask.title}</h1>
                <!-- 文章属性列表 -->
                <dl class="dl-inline">
                    <dt>发布者</dt>
                    <dd>${stuTask.teacher.name}</dd>
                    <dt>更新时间</dt>
                    <dd>${stuTask.hUpdateTime}</dd>
                    <dt>截止时间</dt>
                    <dd>${stuTask.hDeadline}</dd>
                </dl>

            </header>
            <!-- 文章正文部分 -->
            <section class="content">
                ${stuTask.content}
            </section>
            <!-- 文章底部 -->
            <footer>
                <ul class="pager pager-justify">

                </ul>
            </footer>
        </article>

        <div id="upload-file-div">
            <h3>上传作业：</h3>
            <c:if test="${not empty taskFile}">
                <h4>已交：<a href="/file/taskFileDownload.action?taskId=${stuTask.id}"> ${taskFile.fileName} </a>&nbsp;&nbsp;&nbsp;提交时间：${taskFile.hUploadTime}</h4>
                <p>再次上传将覆盖原文件</p>
            </c:if>

            <div id='uploader' class="uploader">
                <div class="uploader-message text-center">
                    <div class="content"></div>
                    <button type="button" class="close">×</button>
                </div>
                <div class="uploader-files file-list file-list-lg" data-drag-placeholder="请拖拽文件到此处"></div>
                <div class="uploader-actions">
                    <div class="uploader-status pull-right text-muted"></div>
                    <button type="button" class="btn btn-link uploader-btn-browse"><i class="icon icon-plus"></i> 选择文件</button>
                    <button type="button" id="start-upload-btn" class="btn btn-link uploader-btn-start"><i class="icon icon-cloud-upload"></i> 开始上传</button>
                </div>
            </div>
        </div>
    </div>

    <script>
        $(function () {
            var uploader = $('#uploader');
            uploader.uploader({
                autoUpload: false,            // 当选择文件后立即自动进行上传操作
                url: '/file/taskFileUpload',  // 文件上传提交地址
                chunk_size: 0,
                limitFilesCount: 1,
                filters: {
                    max_file_size: '50mb'
               },
                multipart_params: {
                    taskId: ${stuTask.id},
                    courseId: ${stuCourse.id}
                }


            });

            uploader.uploader().on('onUploadComplete', function (files) {
                location.href = '/student/taskDetail.action?courseId=${stuCourse.id}&taskId=${stuTask.id}';
            });


        });


    </script>

</body>
</html>
