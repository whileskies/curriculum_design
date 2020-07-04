<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%--
  User: Gao Tian
  Date: 2019/7/1
  Time: 10:08
--%>
<%@ page contentType="text/html;charset=UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>${teaCourse.name}</title>

    <link rel="stylesheet" href="//cdn.bootcss.com/zui/1.9.1/css/zui.min.css">
    <script src="//cdn.bootcss.com/zui/1.8.1/lib/jquery/jquery.js"></script>
    <script src="//cdn.bootcss.com/zui/1.8.1/js/zui.min.js"></script>
    <link href="/lib/uploader/zui.uploader.min.css" rel="stylesheet">
    <script src="/lib/uploader/zui.uploader.min.js"></script>
    <link rel="stylesheet" href="/lib/datatable/zui.datatable.min.css">
    <script src="/lib/datatable/zui.datatable.min.js"></script>
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

        #uploader{
            height: 200px;
            text-align: center;
        }

        .file-list{
            height: 150px;
            overflow-y: scroll;
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
                <li class="active"><a href="/teacher/resource.action?courseId=${teaCourse.id}"><p class="nav-p">资源</p></a></li>
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
        <div id='uploader' class="uploader ">
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

        <div>
            <h3>资源列表</h3>
            <table class="table datatable">
            </table>


        </div>



    </div>


    <script>
        $(function () {
            var uploader = $('#uploader');
            uploader.uploader({
                autoUpload: false,            // 当选择文件后立即自动进行上传操作
                url: '/file/uploadResource',  // 文件上传提交地址
                chunk_size: 0,
                filters: {
                    max_file_size: '500mb'
                },
                multipart_params: {
                    courseId: ${teaCourse.id}
                }

            });

            uploader.uploader().on('onUploadComplete', function (files) {
                location.href = '/teacher/resource.action?courseId=${teaCourse.id}';
            });


            $('.datatable').datatable(
                {
                    sortable: true,
                    data: {
                        cols: [
                            {width: 150, text: '文件名', type: 'string', flex: false, colClass: 'text-center'},
                            {width: 100, text: '时间', type: 'string', flex: false,  colClass: 'text-center'},
                            {width: 60, text: '大小', type: 'string', flex: false, sort: false, colClass: 'text-center'},
                            {width: 60, text: '操作', sort: false, colClass: 'text-center'}
                        ],
                        rows: [
                            <c:forEach items="${resources}" var="r">
                                {checked: false, data: ['${r.fileName}', '${r.hUploadTime}', '${r.hFileSize}',
                                        '<a href="/file/downloadResource.action?resourceId=${r.id}" ><i class="icon icon-download-alt"></i></a> ' +
                                        '&nbsp;&nbsp;<a onclick="confirmDel(\'${r.fileName}\', \'${r.id}\',\'${teaCourse.id}\')"><i class="icon icon-trash"></i></a>']},
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
