<!-- PHP requirement files -->
<?php
require_once "inc/page_setup.php";
$pgTitle = "About Us";
include ('inc/header.php');
?>

</head>

<?php include ('inc/nav.php'); ?>

<!-- Start contents of main page here. -->

<div class="container">
	<div class="row">
		<div class="col-lg-12 col-md-12 col-sm-12 col-xs-12">
			<h1>About</h1>
			<h3>
				This is our Project 3 Page for CT310
			</h3>
		</div>
	</div>
	<div class="row">
		<div class="col-sm-6">
			<!-- Nate's Info -->
			<h2>Nate Barteaux</h2>
			<img src="assets/img/nate.jpg" class="img-circle center-block avatar" alt="nb" width="280" height="290">
			<p style="text-align: center;">
				Nate is a senior at CSU studying applied computing technology.
			</p>
		</div>
		<div class="col-sm-6">
			<!-- Brendon's Info -->
			<h2>Brendon Powley</h2>
			<img src="assets/img/brendon.jpg" class="img-circle center-block avatar" alt="bp" width="280" height="290">
			<p style="text-align: center;">
				Brendon is a junior at CSU studying applied computing technology. His interests include sports, music, and biking.
			</p>
		</div>
	</div>
	<div class="row">
		<div class="col-xs-12">
			<p class="photoCred">All local ingredient images from <a href="https://morguefile.com/">Mourgefile,com</a><br>
				Header logo image by valeria_aksakova from <a href="http://www.freepik.com/">Freepik.com</a></p>
		</div>
	</div>
</div>




<!-- End of contents -->
<?php include('inc/footer.php'); ?>
