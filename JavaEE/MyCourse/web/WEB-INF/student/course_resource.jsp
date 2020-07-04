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
    <title>${stuCourse.name}</title>

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


    </style>
</head>
<body>
    <nav class="navbar navbar-inverse" role="navigation">
        <div class="container-fluid">

            <div class="navbar-header">
                <a class="navbar-brand navbar-font" href="/student/showCourseList.action"><strong class="nav-p">我的课堂</strong> </a>
            </div>

            <ul class="nav navbar-nav">
                <li><a href="/student/notice.action?courseId=${stuCourse.id}"><p class="nav-p">公告</p></a></li>
                <li><a href="/student/task.action?courseId=${stuCourse.id}"><p class="nav-p">作业</p></a></li>
                <li class="active"><a href="/student/resource.action?courseId=${stuCourse.id}"><p class="nav-p">资源</p></a></li>
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
        <h3>资源列表</h3>
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
                            {width: 150, text: '文件名', type: 'string', flex: false, colClass: 'text-center'},
                            {width: 100, text: '时间', type: 'string', flex: false,  colClass: 'text-center'},
                            {width: 60, text: '大小', type: 'string', flex: false, sort: false, colClass: 'text-center'},
                            {width: 60, text: '操作', sort: false, colClass: 'text-center'}
                        ],
                        rows: [
                            <c:forEach items="${resources}" var="r">
                                {checked: false, data: ['${r.fileName}', '${r.hUploadTime}', '${r.hFileSize}',
                                        '<a href="/file/downloadResource.action?resourceId=${r.id}" ><i class="icon icon-download-alt"></i></a> ']},
                            </c:forEach>
                        ]
                    }
                }
            );


        });

    </script>

</body>
</html>
